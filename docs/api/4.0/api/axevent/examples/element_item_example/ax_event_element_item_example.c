/**
 * @file ax_event_key_value_set_example1.c
 *
 * @brief This example illustrates how to use the AXEventKeyValueSet function
 * ax_event_key_value_set_add_key_value() to add a set of key/values to an
 * AXEventKeyValueSet.
 */

#include <glib.h>
#include <axsdk/axevent.h>

static AXEventElementItem*
create_element_item(void);

static void
create_key_value_set(void);


/**
 * This function builds an ElementItem with the following structure
 * <root>
 *   <node1 key1="value1" key2="value2"/>
 *   <node2 key1="value1" key2="value2">
 *     The body of the element
 *   </node2>
 * </root>
 */
static AXEventElementItem*
create_element_item(void)
{
  AXEventElementItem *root;
  AXEventElementItem *node1;
  AXEventElementItem *node2;
  GHashTable *attributes;
  GError *error = NULL;
  gboolean result;

  /* Use the same attributes for all elements, in a real world application
   * the attributes are of course different for different elements.
   */
  attributes = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  g_hash_table_insert(attributes, g_strdup("key1"), g_strdup("value1"));
  g_hash_table_insert(attributes, g_strdup("key2"), g_strdup("value2"));

  root = ax_event_element_item_new("root", "tnsme");
  node1 = ax_event_element_item_new("node1", "tnsme");
  node2 = ax_event_element_item_new("node2", "tnsme");

  if (!ax_event_element_item_set_attributes(node1, attributes, &error)) {
    goto error;
  }
  if (!ax_event_element_item_set_attributes(node2, attributes, &error)) {
    goto error;
  }

  /* Add a body to the last node. */
  if (!ax_event_element_item_set_body(node2, "The body of the element", &error)) {
    goto error;
  }

  if (!ax_event_element_item_add_child(root, node1, &error)) {
    goto error;
  }
  if (!ax_event_element_item_add_child(root, node2, &error)) {
    goto error;
  }

  result = TRUE;

error:
  if (!result) {
    ax_event_element_item_free(root);
    root = NULL;
  }

  g_hash_table_destroy(attributes);
  
  return root;
}

static void
create_key_value_set(void)
{
  AXEventKeyValueSet *set = NULL;
  AXEventElementItem *item = NULL;
  GError *error = NULL;

  /* Create a new AXEventKeyValueSet */
  if ((set = ax_event_key_value_set_new()) == NULL) {
    goto error;
  }

  if ((item = create_element_item()) == NULL) {
    goto error;
  }

  /* Add key/values, in this particual example the key/values of the
   * AXEventKeyValueSet matches the key/values of an active Manual trigger event.
   */
  if (!ax_event_key_value_set_add_key_value(set,
        "topic0", "tnsaxis", "CameraApplicationPlatform", AX_VALUE_TYPE_STRING,
        &error)) {
    goto error;
  }

  if (!ax_event_key_value_set_add_key_value(set,
        "topic1", "tnsme", "Message", AX_VALUE_TYPE_STRING,
        &error)) {
    goto error;
  }

  if (!ax_event_key_value_set_add_key_value(set,
        "message", NULL, item, AX_VALUE_TYPE_ELEMENT,
        &error)) {
    goto error;
  }

  /* The set has been initialized and is ready for use. */

error:
  /* Clean up */

  if (set != NULL) {
    ax_event_key_value_set_free(set);
  }

  if (item != NULL) {
    ax_event_element_item_free(item);
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
