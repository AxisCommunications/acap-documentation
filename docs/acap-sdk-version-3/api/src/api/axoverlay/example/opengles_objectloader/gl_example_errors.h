/*
 * Copyright (C) 2019, Axis Communications AB, LUND, SWEDEN
 */

#ifndef GL_EXAMPLE_ERRORS_H
#define GL_EXAMPLE_ERRORS_H

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Convenience macro for the axoverlay_error_quark function. */
#define AXOVERLAY_ERROR (axoverlay_gl_example_error_quark())

gboolean check_gl_error(GError **error);
gboolean check_egl_error(GError **error);
GQuark axoverlay_gl_example_error_quark(void);

#ifdef __cplusplus
}
#endif

#endif