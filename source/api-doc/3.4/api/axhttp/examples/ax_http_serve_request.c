#include <glib.h>
#include <gio/gio.h>
#include <string.h>
#include <axsdk/axhttp.h>

static void
request_handler(const gchar *path,
    const gchar *method,
    const gchar *query,
    GHashTable *params,
    GOutputStream *output_stream,
    gpointer user_data);

static void
my_output_utility(GDataOutputStream *dos,
  const gchar *fmt,
  ...);

  static void
request_handler(const gchar *path,
    const gchar *method,
    const gchar *query,
    GHashTable *params,
    GOutputStream *output_stream,
    gpointer user_data)
{
  GDataOutputStream *dos;
  GHashTableIter iter;
  gchar *key;
  gchar *value;

  g_message("----------------------------------------");
  g_message("Path: %s", path);
  g_message("Method: %s", method ? method : "(unspecified)");

  if (query != NULL) {
    g_message("Query: %s", query);
  }

  g_message("----------------------------------------");

  dos = g_data_output_stream_new(output_stream);

  g_data_output_stream_put_string(dos, "Content-Type: text/plain\r\n", NULL, NULL);
  g_data_output_stream_put_string(dos, "Status: 200 OK\r\n\r\n", NULL, NULL);

  my_output_utility(dos, "Path: %s\n", path);
  my_output_utility(dos, "Method: %s\n", method ? method : "(unspecified)");

  if (query != NULL) {
    my_output_utility(dos, "Query: %s\n", query);
  }

  if (params != NULL) {
    my_output_utility(dos, "Parameters:\n");

    g_hash_table_iter_init(&iter, params);
    while (g_hash_table_iter_next(&iter, (gpointer*)&key, (gpointer*)&value)) {
      my_output_utility(dos, "%s => %s\n", key, value);
    }
  }

  g_object_unref(dos);
  (void) user_data;
}

static void
my_output_utility(GDataOutputStream *dos,
  const gchar *fmt,
  ...)
{
  va_list ap;
  gchar *tmp_str;

  va_start(ap, fmt);

  g_message("Format: %s", fmt);

  tmp_str = g_strdup_vprintf(fmt, ap);
  g_message("Writing: %s", tmp_str);
  g_data_output_stream_put_string(dos, tmp_str, NULL, NULL);
  g_free(tmp_str);

  va_end(ap);
}

static void
init_signals(void)
{
  struct sigaction sa;

  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGPIPE);
  sa.sa_flags = 0;
  sa.sa_handler = SIG_IGN;
  sigaction (SIGPIPE, &sa, NULL);
}

int main(void)
{
  GMainLoop *loop;
  AXHttpHandler *handler;

  init_signals();

  loop = g_main_loop_new(NULL, FALSE);

  g_message("Creating new handler");

  handler = ax_http_handler_new(request_handler, NULL);

  g_message("Handler: %p", handler);

  g_main_loop_run(loop);

  ax_http_handler_free(handler);

  return 0;
}
