/**
 * @file ax_event_stateless_declaration_example.c
 *
 * @brief This example illustrates how to setup a state less event declaration.
 *
 * Error handling has been omitted for the sake of brevity.
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
  guint declaration;
  AXEventKeyValueSet *set;

  set = ax_event_key_value_set_new();

  /* Initialize an AXEventKeyValueSet that looks like this
   *
   *    tnsaxis:topic0=CameraApplicationPlatform
   * tnsaxis:topic1=MyApplication
   *          event=* <-- the value of the event key is variable
   *
   * The fact that there's a key called "event" in this AXEventKeyValueSet has
   * not semantic meaning other than being the name of the key. 
   */
  ax_event_key_value_set_add_key_values(set,
      NULL,
      "topic0", "tnsaxis", "CameraApplicationPlatform", AX_VALUE_TYPE_STRING,
      "topic1", "tnsaxis", "MyApplication", AX_VALUE_TYPE_STRING,
      "event", NULL, NULL, AX_VALUE_TYPE_BOOL,
      NULL);

  ax_event_key_value_set_mark_as_data(set, "event", NULL, NULL);

  /* The AXEventKeyValueSet has been initialized, now it's time to declare the
   * event.
   */
  ax_event_handler_declare(event_handler, set,
      TRUE, /* Indicates a state less declaration. */
      &declaration,
      declaration_complete,
      NULL,
      NULL);

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
