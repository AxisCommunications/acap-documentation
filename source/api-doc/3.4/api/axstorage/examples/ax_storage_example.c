/**
 * Copyright (C) Axis Communications AB 2013.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <glib.h>
#include <glib/gstdio.h>
#include <syslog.h>
#include <errno.h>

/* AX Storage library. */
#include <axsdk/axstorage.h>

#define APP_NAME "axStorageExample"

/**
 * disk_item_t represents one storage device and its values.
 */
typedef struct {
  AXStorage *storage; /** AXStorage reference. */
  AXStorageType storage_type; /** Storage type */
  gchar *storage_id; /** Storage device name. */
  gchar *storage_path; /** Storage path. */
  guint subscription_id; /** Subscription ID for storage events. */
  gboolean setup; /** TRUE: storage was set up async, FALSE otherwise. */
  gboolean writable; /** Storage is writable or not. */
  gboolean available; /** Storage is available or not. */
  gboolean full; /** Storage device is full or not. */
  gboolean exiting; /** Storage is exiting (going to disappear) or not. */
} disk_item_t;

static GList *disks_list = NULL;
static GMainLoop *loop = NULL;

/* Signals */
static void
handle_sigterm(int signo)
{
  if (loop != NULL) {
    g_main_loop_quit(loop);
  } else {
    exit(EXIT_FAILURE);
  }
}

static void
init_signals(void)
{
  struct sigaction sa;

  sa.sa_flags = 0;

  sigemptyset(&sa.sa_mask);
  sa.sa_handler = handle_sigterm;
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGINT, &sa, NULL);
}

static gboolean
write_data(const gchar *data)
{
  static guint counter = 0;
  GList *node = NULL;
  gboolean ret = TRUE;
  for (node = g_list_first(disks_list); node != NULL;
       node = g_list_next(node)) {

    disk_item_t *item = node->data;

    /* Write data to disk when it is available, writable and has disk space
       and the setup has been done. */
    if (item->available && item->writable && !item->full && item->setup) {
      gchar *filename = g_strdup_printf("%s/%s.log", item->storage_path,
          data);

      FILE *file = g_fopen(filename, "a");
      if (file == NULL) {
        syslog(LOG_WARNING, "Failed to open %s. Error %s.", filename,
            g_strerror(errno));
        ret = FALSE;
      } else {
        g_fprintf(file, "counter: %d\n", ++counter);
        fclose(file);
      }
      g_free(filename);
    }
  }
  return ret;
}


static disk_item_t *
find_disk_item_t(gchar *storage_id)
{
  GList *node = NULL;
  disk_item_t *item = NULL;

  for (node = g_list_first(disks_list); node != NULL;
       node = g_list_next(node)) {

    item = node->data;

    if (g_strcmp0(storage_id, item->storage_id) == 0) {
      return item;
    }
  }
  return NULL;
}

static void
release_disk_cb(gpointer user_data, GError *error)
{
  syslog(LOG_INFO, "Release of %s", (gchar*) user_data);
  if (error != NULL) {
    syslog(LOG_WARNING, "Error while releasing %s: %s", (gchar*) user_data,
        error->message);
    g_error_free(error);
  }
}

static void
free_disk_item_t()
{
  GList *node = NULL;

  for (node = g_list_first(disks_list); node != NULL;
       node = g_list_next(node)) {

    GError *error = NULL;
    disk_item_t *item = node->data;

    if (item->setup) {
      /* NOTE: It is advised to finish all your reading/writing operations
         before releasing the storage device. */
      ax_storage_release_async(item->storage, release_disk_cb,
          item->storage_id, &error);
      if (error != NULL) {
        syslog(LOG_WARNING, "Failed to release %s. Error: %s",
            item->storage_id, error->message);
        g_clear_error(&error);
      } else {
        syslog(LOG_INFO, "Release of %s was successful", item->storage_id);
        item->setup = FALSE;
      }
    }

    ax_storage_unsubscribe(item->subscription_id, &error);
    if (error != NULL) {
      syslog(LOG_WARNING, "Failed to unsubscribe event of %s. Error: %s",
          item->storage_id, error->message);
      g_clear_error(&error);
    } else {
      syslog(LOG_INFO, "Unsubscribed events of %s", item->storage_id);
    }
    g_free(item->storage_id);
    g_free(item->storage_path);
  }
  g_list_free(disks_list);
}

static void
setup_disk_cb(AXStorage *storage, gpointer user_data, GError *error)
{
  GError *ax_error = NULL;
  gchar *storage_id = NULL;
  gchar *path = NULL;
  AXStorageType storage_type;

  if (storage == NULL || error != NULL) {
    syslog(LOG_ERR, "Failed to setup disk. Error: %s", error->message);
    g_error_free(error);
    goto free_variables;
  }

  storage_id = ax_storage_get_storage_id(storage, &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get storage_id. Error: %s",
        ax_error->message);
    g_error_free(ax_error);
    goto free_variables;
  }

  path = ax_storage_get_path(storage, &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get storage path. Error: %s",
        ax_error->message);
    g_error_free(ax_error);
    goto free_variables;
  }

  storage_type = ax_storage_get_type(storage, &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get storage type. Error: %s",
        ax_error->message);
    g_error_free(ax_error);
    goto free_variables;
  }

  disk_item_t *disk = find_disk_item_t(storage_id);
  /* The storage pointer is created in this callback, assign it to
     disk_item_t instance. */
  disk->storage = storage;
  disk->storage_type = storage_type;
  disk->storage_path = g_strdup(path);
  disk->setup = TRUE;

  syslog(LOG_INFO, "Disk: %s has been setup in %s", storage_id, path);
free_variables:
  g_free(storage_id);
  g_free(path);
}

/**
 * Subscribe to the events of the storage.
 *
 * @param storage_id The storage to subscribe to its events.
 * @param user_data  User data to be processed.
 * @param error      Returned errors.
 */
static void
subscribe_cb(gchar *storage_id, gpointer user_data, GError *error)
{
  GError *ax_error = NULL;
  gboolean available;
  gboolean writable;
  gboolean full;
  gboolean exiting;

  if (error != NULL) {
    syslog(LOG_WARNING, "Failed to subscribe to %s. Error: %s", storage_id,
        error->message);
    g_error_free(error);
    return;
  }

  syslog(LOG_INFO, "Subscribe for the events of %s", storage_id);
  disk_item_t *disk = find_disk_item_t(storage_id);

  /* Get the status of the events. */
  exiting = ax_storage_get_status(storage_id, AX_STORAGE_EXITING_EVENT,
      &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get EXITING event for %s. Error: %s",
        storage_id, ax_error->message);
    g_error_free(ax_error);
    return;
  }

  available = ax_storage_get_status(storage_id, AX_STORAGE_AVAILABLE_EVENT,
      &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get AVAILABLE event for %s. Error: %s",
        storage_id, ax_error->message);
    g_error_free(ax_error);
    return;
  }

  writable = ax_storage_get_status(storage_id, AX_STORAGE_WRITABLE_EVENT,
      &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get WRITABLE event for %s. Error: %s",
        storage_id, ax_error->message);
    g_error_free(ax_error);
    return;
  }

  full = ax_storage_get_status(storage_id, AX_STORAGE_FULL_EVENT, &ax_error);
  if (ax_error != NULL) {
    syslog(LOG_WARNING, "Failed to get FULL event for %s. Error: %s",
        storage_id, ax_error->message);
    g_error_free(ax_error);
    return;
  }

  disk->writable = writable;
  disk->available = available;
  disk->exiting = exiting;
  disk->full = full;

  /* If exiting, and the disk was set up before, release it. */
  if (exiting && disk->setup) {
    /* NOTE: It is advised to finish all your reading/writing operations before
       releasing the storage device. */
    ax_storage_release_async(disk->storage, release_disk_cb, storage_id,
        &ax_error);

    if (ax_error != NULL) {
      syslog(LOG_WARNING, "Failed to release %s. Error %s.", storage_id,
          ax_error->message);
      g_error_free(ax_error);
    } else {
      syslog(LOG_INFO, "Release of %s was successful", storage_id);
      disk->setup = FALSE;
    }

  /* Writable implies that the disk is available. */
  } else if (writable && !full && !exiting && !disk->setup) {
    syslog(LOG_INFO, "Setup %s", storage_id);
    ax_storage_setup_async(storage_id, setup_disk_cb, NULL, &ax_error);

    if (ax_error != NULL) {
      /* NOTE: It is advised to try to setup again in case of failure. */
      syslog(LOG_WARNING, "Failed to setup %s, reason: %s", storage_id,
          ax_error->message);
      g_error_free(ax_error);
    } else {
      syslog(LOG_INFO, "Setup of %s was successful", storage_id);
    }
  }
}

static disk_item_t *
new_disk_item_t(gchar *storage_id)
{
  GError *error = NULL;
  disk_item_t *item = NULL;
  guint subscription_id;

  /* Subscribe to disks events. */
  subscription_id = ax_storage_subscribe(storage_id, subscribe_cb, NULL,
      &error);
  if (subscription_id == 0 || error != NULL) {
    syslog(LOG_ERR, "Failed to subscribe to events of %s. Error: %s",
        storage_id, error->message);
    g_clear_error(&error);
    return NULL;
  }

  item = g_new0(disk_item_t, 1);
  item->subscription_id = subscription_id;
  item->storage_id = g_strdup(storage_id);
  item->setup = FALSE;

  return item;
}

gint
main()
{
  GList *disks = NULL;
  GList *node = NULL;
  GError *error = NULL;
  gint ret = EXIT_SUCCESS;

  init_signals();
  openlog(APP_NAME, LOG_PID, LOG_LOCAL4);
  syslog(LOG_INFO, "Start AXStorage application.");

  disks = ax_storage_list(&error);
  if (error != NULL) {
    syslog(LOG_WARNING, "Failed to list storage devices. Error: (%s)",
        error->message);
    g_error_free(error);
    ret = EXIT_FAILURE;
    /* Note: It is advised to get the list more than once, in case of failure.*/
    goto out;
  }

  loop = g_main_loop_new(NULL, FALSE);

  /* Loop through the retrieved disks and subscribe to their events. */
  for (node = g_list_first(disks); node != NULL; node = g_list_next(node)) {
    gchar *disk_name = (gchar *) node->data;
    disk_item_t *item = new_disk_item_t(disk_name);
    if (item == NULL) {
      syslog(LOG_WARNING, "%s is skipped", disk_name);
      g_free(node->data);
      continue;
    }
    disks_list = g_list_append(disks_list, item);
    g_free(node->data);
  }
  g_list_free(disks);

  /* Write contents to two files. */
  gchar *file1 = g_strdup("file1");
  gchar *file2 = g_strdup("file2");
  g_timeout_add(1000, (GSourceFunc) write_data, file1);
  g_timeout_add(1000, (GSourceFunc) write_data, file2);

  /* start the main loop */
  g_main_loop_run(loop);

  free_disk_item_t();
  g_free(file1);
  g_free(file2);
  /* unref the main loop when the main loop has been quit */
  g_main_loop_unref(loop);
out:
  syslog(LOG_INFO, "Finish AXStorage application.");
  return ret;
}
