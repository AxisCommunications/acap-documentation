/**
 * @file ax_event_key_value_set_example2.c
 *
 * @brief This example illustrates how to use the AXEventKeyValueSet function
 * ax_event_key_value_set_add_key_values() to add a set of key/values to an
 * AXEventKeyValueSet.
 */

#include <glib.h>
#include <axsdk/axevent.h>

static void
create_key_value_set(void);

static void
create_key_value_set(void)
{
  AXEventKeyValueSet *set = NULL;
  gint port = 0;
  gboolean state = TRUE;
  GError *error = NULL;

  /* Create a new AXEventKeyValueSet */
  if ((set = ax_event_key_value_set_new()) == NULL) {
    goto error;
  }

  /* Add key/values, in this particual example the key/values of the
   * AXEventKeyValueSet matches the key/values of an active Manual trigger event.
   */
  if (!ax_event_key_value_set_add_key_values(set, &error,
        "topic0", "tns1", "Device", AX_VALUE_TYPE_STRING,
        "topic1", "tnsaxis", "IO", AX_VALUE_TYPE_STRING,
        "topic2", "tnsaxis", "VirtualPort", AX_VALUE_TYPE_STRING,
        "port", NULL, &port, AX_VALUE_TYPE_INT,
        "state", NULL, &state, AX_VALUE_TYPE_BOOL,
        NULL)) {
    goto error;
  }

  /* The set has been initialized and is ready for use. */

error:
  /* Clean up */

  if (set != NULL) {
    ax_event_key_value_set_free(set);
  }

  if (error != NULL) {
    g_message("Error: %s", error->message);
    g_error_free(error);
  }
}

gint main(void)
{
  GMainLoop *loop;

  create_key_value_set();

  /* Create and start the GMainLoop */
  loop = g_main_loop_new(NULL, FALSE);

  g_main_loop_run(loop);

  return 0;
}
