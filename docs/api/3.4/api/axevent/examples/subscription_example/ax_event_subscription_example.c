/**
 * @file ax_event_subscription_example.c
 *
 * @brief This example illustrates how to setup an subscription to the
 * manual trigger event.
 *
 * Error handling has been omitted for the sake of brevity.
 */

#include <glib.h>
#include <glib-object.h>
#include <axsdk/axevent.h>

static void
subscription_callback(guint subscription,
    AXEvent *event, guint *token);

static guint
subscribe_to_manual_trigger_port(AXEventHandler *event_handler,
    gint port, guint *token);

static void
subscription_callback(guint subscription,
    AXEvent *event, guint *token)
{
  const AXEventKeyValueSet *key_value_set;
  gint port;
  gboolean state;

  /* The subscription id is not used in this example. */
  (void)subscription;

  /* Extract the AXEventKeyValueSet from the event. */
  key_value_set = ax_event_get_key_value_set(event);

  /* Get the manual trigger port. */
  ax_event_key_value_set_get_integer(key_value_set,
        "port", NULL, &port, NULL);

  /* Get the state of the manual trigger port . */
  ax_event_key_value_set_get_boolean(key_value_set,
        "state", NULL, &state, NULL);

  /* Print a helpfull message. */
  if (state) {
    g_message("Manual trigger port %d is high", port);
  } else {
    g_message("Manual trigger port %d is low", port);
  }

  g_message("And here's the token: %d", *token);

  ax_event_free(event);
}

static guint
subscribe_to_manual_trigger_port(AXEventHandler *event_handler,
    gint port, guint *token)
{
  AXEventKeyValueSet *key_value_set;
  guint subscription;

  key_value_set = ax_event_key_value_set_new();

  /* Initialize an AXEventKeyValueSet that matches the manual trigger event.
   *
   * tns1:topic0=Device
   * tnsaxis:topic1=IO
   * tnsaxis:topic2=VirtualPort
   * port=&port  <-- Subscribe to "port" input argument
   * state=*     <-- Subscribe to all states
   */
  ax_event_key_value_set_add_key_values(key_value_set,
        NULL,
        "topic0", "tns1", "Device", AX_VALUE_TYPE_STRING,
        "topic1", "tnsaxis", "IO", AX_VALUE_TYPE_STRING,
        "topic2", "tnsaxis", "VirtualPort", AX_VALUE_TYPE_STRING,
        "port", NULL, &port, AX_VALUE_TYPE_INT,
        "state", NULL, NULL, AX_VALUE_TYPE_BOOL,
        NULL);

  /* Time to setup the subscription. Use the "token" input argument as
   * input data to the callback function "subscription callback"
   */
  ax_event_handler_subscribe(event_handler, key_value_set,
        &subscription, (AXSubscriptionCallback)subscription_callback, token,
        NULL);

  /* The key/value set is no longer needed */
  ax_event_key_value_set_free(key_value_set);

  return subscription;
}

int main(void)
{
  GMainLoop *main_loop;
  AXEventHandler *event_handler;
  guint subscription;
  gint port = 1;
  guint token = 1234;

  main_loop = g_main_loop_new(NULL, FALSE);

  event_handler = ax_event_handler_new();

  subscription = subscribe_to_manual_trigger_port(event_handler,
    port, &token);

  g_main_loop_run(main_loop);

  ax_event_handler_unsubscribe(event_handler, subscription, NULL);

  ax_event_handler_free(event_handler);

  return 0;
}
