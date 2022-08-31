/*
 * Copyright (C) 2020, Axis Communications AB, LUND, SWEDEN
 */

/*
 * In this example, a simple triangle in an 1920 x 1080 overlay is rendered
 * repetetively (once every RENDER_T ms). This example is suitable for
 * performance measurements on the OpenGL axoverlay backend.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <syslog.h>
#include <math.h>
#include <syslog.h>
#include <glib.h>
#include <glib-unix.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <glib/gstdio.h>
#include <axoverlay.h>
#include <gio/gio.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLES2/gl2ext.h>
#include <EGL/eglext.h>
#include <axoverlay.h>

#define OVL_WIDTH 1920
#define OVL_HEIGHT 1080
#define RENDER_T 33

static gboolean
signal_handler(gpointer data)
{
  GMainLoop *main_loop = (GMainLoop *) data;
  g_main_loop_quit(main_loop);
  return G_SOURCE_REMOVE;
}

static gint overlay_id1 = -1;

struct program_struct {
  GLuint shaderProgram;
  GLuint vertexShader;
  GLuint fragmentShader;
};

static program_struct* the_program = NULL;

gboolean render_trigger_redraw(gpointer data)
{
  GError *error = NULL;
  axoverlay_redraw(&error);
  if (error) {
    syslog(LOG_ERR, "%s: Failed to trigger redraw using axoverlay: %s\n",
        __func__, error->message);
    return FALSE;
  }
  return TRUE;
}

GLbyte vShaderStr[] =
  "attribute vec4 vPosition; \n"
  "void main() \n"
  "{ \n"
  "  gl_Position = vPosition; \n"
  "} \n";

GLbyte fShaderStr[] =
  "precision mediump float;\n"
  "void main()\n"
  "{\n"
  "  float x_gradient = gl_FragCoord.x / 512.0;\n"
  "  float y_gradient = gl_FragCoord.y / 512.0;\n"
  "  gl_FragColor = vec4(x_gradient * y_gradient, y_gradient, x_gradient, 1.0);\n"
  "}\n";

static gboolean
check_gl_error(const char *context)
{
  gboolean had_error = FALSE;
  GLenum err = glGetError();
  gchar *msg;

  while(err != GL_NO_ERROR) {
    had_error = TRUE;
    switch(err) {
    case GL_INVALID_OPERATION:
      msg = (gchar*)"glGetError() has reported an INVALID_OPERATION error";
      break;
    case GL_INVALID_ENUM:
      msg = (gchar*)"glGetError() has reported an INVALID_ENUM error";
      break;
    case GL_INVALID_VALUE:
      msg = (gchar*)"glGetError() has reported an INVALID_VALUE error";
      break;
    case GL_OUT_OF_MEMORY:
      msg = (gchar*)"glGetError() has reported an OUT_OF_MEMORY error";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      msg = (gchar*)"glGetError() has reported an INVALID_FRAMEBUFFER_OPERATION error";
      break;
    default:
      msg = (gchar*)"glGetError() has reported an UNKNOWN_ERROR";
      break;
    }
    syslog(LOG_INFO, "%s: %s", context, msg);
    err = glGetError();
  }
  return had_error;
}

static void
init_render(void)
{
  glActiveTexture(GL_TEXTURE0);
  check_gl_error("init_render - glActiveTexture");
  glClearColor(0.0f, 1.0f, 1.0f, 0.5f);
  check_gl_error("init_render - glClearColor");
  glClear(GL_COLOR_BUFFER_BIT);
  check_gl_error("init_render - glClear");
  glDepthRangef(0.1f, 10.0f);
  check_gl_error("init_render - glDepthRange");
}

static GLuint
LoadShader(GLenum type, const char *shaderSrc)
{
  GLuint shader;
  GLint compiled;

  /* Create the shader object */
  shader = glCreateShader(type);
  check_gl_error("LoadShader - glCreateShader");
  if(shader == 0) {
    return 0;
  }

  /* Load the shader source */
  glShaderSource(shader, 1, &shaderSrc, NULL);
  check_gl_error("LoadShader - glShaderSource");

  /* Compile the shader */
  glCompileShader(shader);
  check_gl_error("LoadShader - glCompileShader");

  /* Check the compile status */
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  check_gl_error("LoadShader - glGetShaderiv");

  if(!compiled)
  {
    GLint infoLen = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

    if(infoLen > 1)
    {
      char* infoLog = (char *)malloc(sizeof(char) * infoLen);
      glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
      printf("Error compiling shader:\n%s\n", infoLog);
      free(infoLog);
    }
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

static void
init_shaders(void)
{
  /* create shader program */
  the_program->vertexShader = LoadShader(GL_VERTEX_SHADER, (const char *)vShaderStr);
  check_gl_error("render_overlay_cb - LoadShader (vertex)");

  the_program->fragmentShader = LoadShader(GL_FRAGMENT_SHADER, (const char *)fShaderStr);
  check_gl_error("render_overlay_cb - LoadShader (fragment)");

  the_program->shaderProgram = glCreateProgram();
  check_gl_error("Could not create shader program");
  if (the_program->shaderProgram == 0) {
    return;
  }

  glAttachShader(the_program->shaderProgram, the_program->vertexShader);
  check_gl_error("render_overlay_cb - glAttachShader (vertex)");

  glAttachShader(the_program->shaderProgram, the_program->fragmentShader);
  check_gl_error("render_overlay_cb - glAttachShader (fragment)");

  glLinkProgram(the_program->shaderProgram);
  check_gl_error("render_overlay_cb - glLinkProgram");

  /* Always detach shaders after a successful link*/
  glDetachShader(the_program->shaderProgram, the_program->vertexShader);
  glDetachShader(the_program->shaderProgram, the_program->fragmentShader);
}

static void
render_triangle(void)
{
  /* a simple triangle */
  static const GLfloat g_vertex_buffer_data[] = {
         -0.5f, -0.5f, -1.0f, 1.0f,
          0.5f, -0.5f, -1.0f, 1.0f,
          0.0f,  0.5f, -1.0f, 1.0f
          };

  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);
  check_gl_error("render_triangle - glDepthFunc");

  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);
  check_gl_error("render_triangle - glClear");

  glUseProgram(the_program->shaderProgram);
  check_gl_error("render_triangle - glUseProgram");

  GLint locVPosition = glGetAttribLocation(the_program->shaderProgram, "vPosition");
  check_gl_error("render_triangle - glGetAttribLocation");
  glEnableVertexAttribArray(locVPosition);
  check_gl_error("render_triangle - glEnableVertexAttribArray");
  glVertexAttribPointer(locVPosition, 4, GL_FLOAT, GL_FALSE, 0, &g_vertex_buffer_data[0]);
  check_gl_error("render_triangle - glVertexAttribPointer");
  glDrawArrays(GL_TRIANGLES, 0, 3);
  check_gl_error("render_triangle - glDrawArrays");

}

static void
render_overlay_cb(gpointer render_context, gint id,
                   struct axoverlay_stream_data *stream,
                   enum axoverlay_position_type postype, gfloat overlay_x,
                   gfloat overlay_y, gint overlay_width, gint overlay_height,
                   gpointer user_data)
{
  init_render();
  render_triangle();
}

static void
cleanup_shaders()
{
  glDeleteShader(the_program->vertexShader);
  glDeleteShader(the_program->fragmentShader);
  glDeleteProgram(the_program->shaderProgram);
  free(the_program);
}

int
main(int argc, char **argv)
{
  struct axoverlay_settings settings;
  struct axoverlay_overlay_data data1;
  GError *error = NULL;
  GMainLoop *main_loop = NULL;

  /*
   * Run as a dameon so that overlays are kept
   * even after the program returns.
   */
  if (daemon(0, 0) != 0) {
    syslog(LOG_ERR, "Daemon failed: %m");
    return 1;
  }

  main_loop = g_main_loop_new(NULL, FALSE);

  g_unix_signal_add(SIGINT, signal_handler, main_loop);
  g_unix_signal_add(SIGTERM, signal_handler, main_loop);

  /* Add init code */
  axoverlay_init_axoverlay_settings(&settings);

  settings.render_callback = render_overlay_cb;
  settings.adjustment_callback = NULL;
  settings.select_callback = NULL;
  settings.backend = AXOVERLAY_OPENGLES_BACKEND;

  axoverlay_init(&settings, &error);
  if (error != NULL) {
    syslog(LOG_ERR, "Failed to initialize axoverlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  the_program = (program_struct*)g_malloc0(sizeof(program_struct));

  init_shaders();

  axoverlay_init_overlay_data(&data1);
  data1.postype = AXOVERLAY_CUSTOM_NORMALIZED;
  data1.anchor_point = AXOVERLAY_ANCHOR_CENTER;
  data1.width = OVL_WIDTH;
  data1.height = OVL_HEIGHT;
  data1.x = 0.0;
  data1.y = 0.0;
  data1.scale_to_stream = FALSE;
  data1.colorspace = AXOVERLAY_COLORSPACE_ARGB32;

  overlay_id1 = axoverlay_create_overlay(&data1, NULL, &error);
  if (error != NULL) {
    syslog(LOG_ERR, "Failed to create first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* Start render loop */
  g_timeout_add(RENDER_T, render_trigger_redraw, NULL);

  g_main_loop_run(main_loop);

  /* Add cleanup code here */
  axoverlay_destroy_overlay(overlay_id1, &error);
  if (error != NULL) {
    syslog(LOG_ERR, "Failed to destroy first overlay: %s", error->message);
    g_error_free(error);
    return 0;
  }

  cleanup_shaders();

  axoverlay_cleanup();

  g_main_loop_unref(main_loop);

  return 0;
}
