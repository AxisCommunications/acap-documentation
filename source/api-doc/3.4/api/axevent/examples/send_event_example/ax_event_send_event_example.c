#include <glib.h>
#include <glib-object.h>
#include <axsdk/axevent.h>
#include <string.h>

typedef struct _AppData
{
  AXEventHandler *handler;
  guint declaration;
  guint timer;
  guint ticks;
} AppData;

static void
declaration_complete(guint declaration, AppData *app_data);

static gboolean
send_event(AppData *app_data);

static void
setup_app_data(AppData *app_data);

static void
declaration_complete(guint declaration, AppData *app_data)
{
  /* The declaration id is not used in this example */
  (void)declaration;

  g_message("Declaration complete");

  /* Set up a timer to be called every second */
  app_data->timer = g_timeout_add_seconds(1,
      (GSourceFunc)send_event,
      app_data);
}

static gboolean
send_event(AppData *app_data)
{
  AXEventKeyValueSet *set;
  AXEvent *event;
  GTimeVal time_stamp;

  app_data->ticks += 1;

  set = ax_event_key_value_set_new();

  /* Add the variable elements of the event to the set */
  ax_event_key_value_set_add_key_value(set,
      "ticks", NULL, &app_data->ticks, AX_VALUE_TYPE_INT,
      NULL);

  /* Use the current time as timestamp in the event */
  g_get_current_time(&time_stamp);

  /* Create the event */
  event = ax_event_new(set, &time_stamp);

  ax_event_key_value_set_free(set);

  /* Send the event */
  ax_event_handler_send_event(app_data->handler,
      app_data->declaration,
      event,
      NULL);

  ax_event_free(event);

  /* Returning TRUE keeps the timer going */
  return TRUE;
}

static void
setup_app_data(AppData *app_data)
{
  AXEventHandler *handler;
  AXEventKeyValueSet *set;
  guint declaration;
  GError *error = NULL;

  set = ax_event_key_value_set_new();

  if (!ax_event_key_value_set_add_key_values(set, &error,
      "topic0", "tnsaxis", "CameraApplicationPlatform", AX_VALUE_TYPE_STRING,
      "topic1", "tnsaxis", "MyTickerApp", AX_VALUE_TYPE_STRING,
      "ticks", NULL, NULL, AX_VALUE_TYPE_INT,
      NULL)) {
    g_message("1: %s", error->message);
  }

  ax_event_key_value_set_mark_as_data(set, "ticks", NULL, NULL);

  handler = ax_event_handler_new();

  if (!ax_event_handler_declare(handler, set,
      TRUE,
      &declaration,
      (AXDeclarationCompleteCallback)declaration_complete,
      app_data,
      &error)) {
    g_message("%s", error->message);
  }

  memset(app_data, 0, sizeof(AppData));
  app_data->handler = handler;
  app_data->declaration = declaration;
}

gint main(void)
{
  GMainLoop *loop;
  AppData app_data;

  setup_app_data(&app_data);

  loop = g_main_loop_new(NULL, FALSE);

  g_main_loop_run(loop);

  return 0;
}
