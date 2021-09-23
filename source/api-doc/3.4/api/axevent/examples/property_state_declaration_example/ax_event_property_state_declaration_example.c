/**
 * @file ax_event_property_state_declaration_example.c
 *
 * @brief This example illustrates how to setup a property state declaration.
 * Error handling has been emitted for the sake of brevity.
 */

#include <glib.h>
#include <glib-object.h>
#include <axsdk/axevent.h>

static void
declaration_complete(guint declaration, gpointer user_data);

static guint
setup_declaration(AXEventHandler *event_handler);

static void
declaration_complete(guint declaration, gpointer user_data)
{
  /* This callback will be called when the declaration has been registered
   * with the event system. The event declaration can now be used to send
   * events.
   */
  ((void)user_data);
  g_message("Declaration complete for: %d", declaration);
}

static guint
setup_declaration(AXEventHandler *event_handler)
{
  guint declaration = 0;
  AXEventKeyValueSet *set = NULL;
  gboolean enabled = TRUE;

  set = ax_event_key_value_set_new();

  /* Initialize an AXEventKeyValueSet that looks like this
   *
   *    tnsaxis:topic0=CameraApplicationPlatform
   * tnsaxis:topic1=MyApplication
   *        feature=myfeature
   *        enabled=1 <-- The initial value will be set to 1/true
   */
  if (!ax_event_key_value_set_add_key_values(set, NULL,
      "topic0", "tnsaxis", "CameraApplicationPlatform", AX_VALUE_TYPE_STRING,
      "topic1", "tnsaxis", "MyApplication", AX_VALUE_TYPE_STRING,
      "feature", NULL, "myfeature", AX_VALUE_TYPE_STRING,
      "enabled", "tnsaxis", &enabled, AX_VALUE_TYPE_BOOL, NULL)) {
    g_warning("Could not add key values to ax_event_key_value_set");

    goto error;
  }

  ax_event_key_value_set_mark_as_source(set, "feature", NULL, NULL);
  ax_event_key_value_set_mark_as_data(set, "enabled", "tnsaxis", NULL);
  ax_event_key_value_set_mark_as_user_defined(set, "feature", NULL, "tag-on-key-value", NULL);
  ax_event_key_value_set_mark_as_user_defined(set, "topic1", "tnsaxis", "tag-on-key-value", NULL);
  ax_event_key_value_set_add_nice_names(set, "enabled", "tnsaxis", "Key nice name", "Value nice name", NULL);

  /* The AXEventKeyValueSet has been initialized, now it's time to declare the
   * event.
   */
  if (!ax_event_handler_declare(event_handler, set, FALSE, /* Indicated a property state */
      &declaration, declaration_complete, NULL, NULL)) {
    g_warning("Could not declare");

    goto error;
  }

error:
  ax_event_key_value_set_free(set);

  return declaration;
}

gint main(void)
{
  GMainLoop *loop;
  AXEventHandler *event_handler;
  guint declaration;

  /* Create an AXEventHandler */
  event_handler = ax_event_handler_new();

  declaration = setup_declaration(event_handler);

  g_message("Got declaration: %d", declaration);

  /* Create and start the GMainLoop */
  loop = g_main_loop_new(NULL, FALSE);

  g_main_loop_run(loop);

  ax_event_handler_undeclare(event_handler,
      declaration,
      NULL);

  ax_event_handler_free(event_handler);

  return 0;
}
