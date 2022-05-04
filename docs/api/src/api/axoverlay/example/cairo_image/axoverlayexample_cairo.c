/*
 * Copyright (C) 2017, Axis Communications AB, LUND, SWEDEN
 */

/*
 * Simple example application that demonstrates how axoverlay is used.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <glib-unix.h>
#include <cairo/cairo.h>
#include <axoverlay.h>

#define OVERLAY_WIDTH 144
#define OVERLAY_HEIGHT 144

#define PIE_RADIUS 64
#define ANIMATION_FPS 10

#define M_PI 3.14

static gint animation_timer = -1;
static gdouble pie_angle = 0.0;
static gint overlay_id = -1;

static gboolean
signal_handler(gpointer data)
{
  GMainLoop *main_loop = (GMainLoop *) data;
  g_main_loop_quit(main_loop);
  return G_SOURCE_REMOVE;
}

static gboolean
update_overlay_cb(gpointer data)
{
  GError *error = NULL;

  /* Update the angle of the pie shape */
  pie_angle += 5.0;
  if (pie_angle >= 360.0) {
    pie_angle -= 360.0;
  }

  /* Request a redraw of the overlay */
  axoverlay_redraw(&error);
  if (error != NULL) {
    /*
     * If redraw fails then it is likely due to that overlayd has
     * crashed. Don't exit instead wait for overlayd to restart and
     * for axoverlay to restore the connection.
     */
    printf("Failed to redraw overlay (%d): %s\n", error->code, error->message);
    g_error_free(error);
  }

  return G_SOURCE_CONTINUE;
}

static void
render_overlay_cb(gpointer render_context, gint id,
                   struct axoverlay_stream_data *stream,
                   enum axoverlay_position_type postype, gfloat overlay_x,
                   gfloat overlay_y, gint overlay_width, gint overlay_height,
                   gpointer user_data)
{
  cairo_t *cr = render_context;
  gdouble x = OVERLAY_WIDTH/2;
  gdouble y = OVERLAY_HEIGHT/2;
  gdouble radius = PIE_RADIUS;
  gdouble angle1 = 0;
  gdouble angle2 = pie_angle*(M_PI/180.0);

  /* Clear background */
  cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.0);
  cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
  cairo_rectangle(cr, 0, 0, OVERLAY_WIDTH, OVERLAY_HEIGHT);
  cairo_fill(cr);

  /* Draw a filled pie shape */
  cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 1.0);
  cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
  cairo_set_line_width(cr, 5.0);
  cairo_arc(cr, x, y, radius, angle1, angle2);
  cairo_line_to(cr, x, y);
  cairo_line_to(cr, x+PIE_RADIUS, y);
  cairo_fill(cr);
}

int
main(int argc, char **argv)
{
  GError *error = NULL;
  GMainLoop *main_loop = NULL;

  /* Create a glib main loop */
  main_loop = g_main_loop_new(NULL, FALSE);

  g_unix_signal_add(SIGINT, signal_handler, main_loop);
  g_unix_signal_add(SIGTERM, signal_handler, main_loop);

  if(!axoverlay_is_backend_supported(AXOVERLAY_CAIRO_IMAGE_BACKEND)) {
    printf("AXOVERLAY_CAIRO_IMAGE_BACKEND is not supported");
    return 1;
  }

  /* Initialize the library */
  struct axoverlay_settings settings;
  axoverlay_init_axoverlay_settings(&settings);
  settings.render_callback = render_overlay_cb;
  settings.adjustment_callback = NULL;
  settings.select_callback = NULL;
  settings.backend = AXOVERLAY_CAIRO_IMAGE_BACKEND;
  axoverlay_init(&settings, &error);
  if (error != NULL) {
    printf("Failed to initialize axoverlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Create an overlay */
  struct axoverlay_overlay_data data;
  axoverlay_init_overlay_data(&data);
  data.postype = AXOVERLAY_CUSTOM_NORMALIZED;
  data.anchor_point = AXOVERLAY_ANCHOR_CENTER;
  data.x = 0.0;
  data.y = 0.0;
  data.width = OVERLAY_WIDTH;
  data.height = OVERLAY_WIDTH;
  data.colorspace = AXOVERLAY_COLORSPACE_ARGB32;
  overlay_id = axoverlay_create_overlay(&data, NULL, &error);
  if (error != NULL) {
    printf("Failed to create first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Draw overlays */
  axoverlay_redraw(&error);
  if (error != NULL) {
    printf("Failed to draw overlays: %s", error->message);
    axoverlay_destroy_overlay(overlay_id, &error);
    axoverlay_cleanup();
    g_error_free(error);
    return 1;
  }

  /* Start animation timer */
  animation_timer = g_timeout_add(1000/ANIMATION_FPS, update_overlay_cb, NULL);

  /* Enter main loop */
  g_main_loop_run(main_loop);

  /* Destroy the overlay */
  axoverlay_destroy_overlay(overlay_id, &error);
  if (error != NULL) {
    printf("Failed to destroy first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Release library resources */
  axoverlay_cleanup();

  /* Release the animation timer */
  g_source_remove(animation_timer);

  /* Release main loop */
  g_main_loop_unref(main_loop);

  return 0;
}
