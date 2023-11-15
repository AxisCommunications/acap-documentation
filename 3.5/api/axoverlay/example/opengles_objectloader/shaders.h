/*
 * Copyright (C) 2019, Axis Communications AB, LUND, SWEDEN
 */
#ifndef SHADERS_H
#define SHADERS_H

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shader_program_t {
  GLuint vertex_shader;
  GLuint frag_shader;
  GLuint program;
} shader_program_t;

/*
 * Creates a shader program by attaching the corresponding
 * vertex and fragment shader
 *
 * Params: shader_name - name of the shader, the vertex and fragment shader
 *                       files have ".vert" and ".frag" extensions respectively
 *
 * Returns: struct that points to shader program handle
 */
shader_program_t shader_create_program(const char *shader_name);

/*
 * Destroy a shader program
 *
 * Params: shader_program - struct that points to shader program handle
 */
void shader_destroy_program(shader_program_t shader_program);

shader_program_t shader_create_and_link_program(const char *vertex_shader_fpath, const char *frag_shader_fpath);

GLuint shader_create(const char *fpath, GLenum shader_type);

#ifdef __cplusplus
}
#endif

#endif
