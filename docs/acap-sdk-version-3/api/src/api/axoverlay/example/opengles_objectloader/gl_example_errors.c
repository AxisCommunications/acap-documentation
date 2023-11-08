/*
 * Copyright (C) 2017, Axis Communications AB, LUND, SWEDEN
 */

#include "gl_example_errors.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <string.h>

#include "axoverlay.h"

#define AXOVERLAY_GL_EXAMPLE_ERROR_QUARK_STRING "Axoverlay - Gl example error"

GQuark
axoverlay_gl_example_error_quark(void)
{
  return g_quark_from_static_string(AXOVERLAY_GL_EXAMPLE_ERROR_QUARK_STRING);
}

gboolean
check_gl_error(GError **error)
{
  gboolean had_error = FALSE;
  GLenum err = glGetError();


  while(err != GL_NO_ERROR) {
    had_error = TRUE;
    switch(err) {
    case GL_INVALID_OPERATION:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "glGetError() has reported an INVALID_OPERATION error");
      break;
    case GL_INVALID_ENUM:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "glGetError() has reported an INVALID_ENUM error");
      break;
    case GL_INVALID_VALUE:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "glGetError() has reported an INVALID_VALUE error");
      break;
    case GL_OUT_OF_MEMORY:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "glGetError() has reported an OUT_OF_MEMORY error");
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
            "glGetError() has reported an INVALID_FRAMEBUFFER_OPERATION error");
      break;
    default:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "glGetError() has reported an UNKNOWN_ERROR");
      break;
    }
    err = glGetError();
  }
  return had_error;
}

gboolean
check_egl_error(GError **error)
{
  gboolean had_error = FALSE;
  GLenum err = eglGetError();

  while(err != EGL_SUCCESS) {
    had_error = TRUE;
    switch(err) {
    case EGL_NOT_INITIALIZED:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a NOT_INITIALIZED error");
      break;
    case EGL_BAD_ACCESS:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_ACCESS error");
      break;
    case EGL_BAD_ALLOC:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_ALLOC error");
      break;
    case EGL_BAD_ATTRIBUTE:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_ATTRIBUTE error");
      break;
    case EGL_BAD_CONFIG:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_CONFIG error");
      break;
    case EGL_BAD_CONTEXT:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_CONTEXT error");
      break;
    case EGL_BAD_CURRENT_SURFACE:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_CURRENT_SURFACE error");
      break;
    case EGL_BAD_DISPLAY:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_DISPLAY error");
      break;
    case EGL_BAD_MATCH:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_MATCH error");
      break;
    case EGL_BAD_NATIVE_PIXMAP:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_NATIVE_PIXMAP error");
      break;
    case EGL_BAD_NATIVE_WINDOW:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_NATIVE_WINDOW error");
      break;
    case EGL_BAD_PARAMETER:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                 "eglGetError() has reported a BAD_PARAMETER error");
      break;
    case EGL_BAD_SURFACE:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a BAD_SURFACE error");
      break;
    case EGL_CONTEXT_LOST:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported a CONTEXT_LOST error");
      break;
    default:
      g_set_error(error, AXOVERLAY_ERROR, AXOVERLAY_ERROR_INTERNAL,
                  "eglGetError() has reported an UNKNOWN ERROR");
      break;
    }
    err = eglGetError();
  }
  return had_error;
}
