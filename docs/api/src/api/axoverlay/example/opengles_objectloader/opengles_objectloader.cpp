/*
 * Copyright (C) 2019, Axis Communications AB, LUND, SWEDEN
 */

/*
 * In this example, either a cube or a "stormwind" banner is rendered once.
 * This example shows how .obj files (often created in blender) are loaded
 * and, in conjunction with .mtl and .bmp files are used to render 3D graphics
 * in OpenGL.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <glib-unix.h>
#include <axoverlay.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLES2/gl2ext.h>
#include <EGL/eglext.h>
#include "config.h"
#include "render.h"
#include <syslog.h>
#include <unistd.h>

#define OVERLAY_WIDTH 1024
#define OVERLAY_HEIGHT 1024

static gint overlay_id = -1;

static gboolean
signal_handler(gpointer data)
{
  GMainLoop *main_loop = (GMainLoop *) data;
  g_main_loop_quit(main_loop);
  return G_SOURCE_REMOVE;
}

static void
render_overlay_cb(gpointer render_context, gint id,
                   struct axoverlay_stream_data *stream,
                   enum axoverlay_position_type postype, gfloat overlay_x,
                   gfloat overlay_y, gint overlay_width, gint overlay_height,
                   gpointer user_data)
{
  struct config* local_config = get_config();
  /* The render_init method loads the obj to OpenGL ES which takes some time.
  In a situation where the overlay is re-rendered continuously, the render_init
  method should not be called more than necessary */
  render_init(local_config);
  render(local_config);
}

int
main(int argc, char **argv)
{
  GError *error = NULL;
  GMainLoop *main_loop = NULL;
  int c;
  const char* obj_name = NULL;
  float rot_angle1 = 0.0;
  float rot_angle2 = 0.0;
  float scale_factor = 1.0;

  while ((c = getopt (argc, argv, "ho:p:t:s:")) != -1)
  {
    switch (c) {
      case 'o':
        obj_name = optarg;
        break;
      case 'p':
        rot_angle1 = atof(optarg);
        break;
      case 't':
        rot_angle2 = atof(optarg);
        break;
      case 's':
        scale_factor = atof(optarg);
        break;
      case 'h':
      default:
        printf("\nThe syntax for executing the OpenGL ES example is:\n");
        printf("\n ./axoverlaygles -f obj_name -p rot_angle 1 -t rot_angle2 -s scale\n");
        printf("\n where:\n\n");
        printf("     obj_name is the name of the object to be rendered\n");
        printf("     rot_angle 1 is a normalized rotation angle (value between -1.0 and 1.0\n");
        printf("     rot_angle 2 is a normalized rotation angle (value between -1.0 and 1.0\n");
        printf("     scale is the scale factor for the object\n");
        printf("\nExample: ./axoverlaygles -o cube -p 0.63 -t 0.63 -s 1.0\n");
        printf("\nSee the 'README' file for more details\n\n");
        return 0;
    }
  }

  GMainContext *context = g_main_context_default();

  /* Create a glib main loop */
  main_loop = g_main_loop_new(context, FALSE);

  g_unix_signal_add(SIGINT, signal_handler, main_loop);
  g_unix_signal_add(SIGTERM, signal_handler, main_loop);

  config_init(context, obj_name, rot_angle1, rot_angle2, scale_factor);

  /* Initialize the library */
  struct axoverlay_settings settings;

  axoverlay_init_axoverlay_settings(&settings);

  settings.render_callback = render_overlay_cb;
  settings.adjustment_callback = NULL;
  settings.select_callback = NULL;
  settings.backend = AXOVERLAY_OPENGLES_BACKEND;
  axoverlay_init(&settings, &error);
  if (error) {
    syslog(LOG_ERR, "Failed to initialize axoverlay: %s", error->message);
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
  if (error) {
    syslog(LOG_ERR, "Failed to create overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Draw overlays */
  axoverlay_redraw(&error);
  if (error) {
    syslog(LOG_ERR, "Failed to draw overlays: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Enter main loop */
  g_main_loop_run(main_loop);

  /* Destroy the overlay */
  axoverlay_destroy_overlay(overlay_id, &error);
  if (error) {
    syslog(LOG_ERR, "Failed to destroy overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Release library resources */
  axoverlay_cleanup();

  /* Release main loop */
  g_main_loop_unref(main_loop);

  return 0;
}
