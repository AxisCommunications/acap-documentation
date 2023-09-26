/*
 * Copyright (C) 2019, Axis Communications AB, LUND, SWEDEN
 */

#include "shaders.h"

#include "../../src/error_handler.h"

#include <stdlib.h>
#include <stdio.h>

#include <string.h>

static char *_shader_read(const char *fpath, gint *len)
{
  FILE * fptr = NULL;
  size_t read_elements;
  fptr = fopen(fpath, "rb");
  if (!fptr)
    return 0;

  fseek(fptr, 0, SEEK_END);
  *len = ftell(fptr);
  fseek(fptr, 0 ,SEEK_SET);

  char *shaderSource = (char *)g_malloc(sizeof(char) * (*len));

  read_elements = fread(shaderSource, *len, 1, fptr);
  if (read_elements != 1) {
    ERROR("_shader_read error");
  }
  fclose(fptr);

  return shaderSource;
}

GLuint shader_create(const char *fpath, GLenum shader_type)
{
  /* create shader object */
  gint len = 0;
  GLuint shader = glCreateShader(shader_type);
  char *shaderSource = _shader_read(fpath, &len);

  /* link source to shader object */
  glShaderSource(shader, 1, (const char**)&shaderSource, &len);

  /* compile shader */
  glCompileShader(shader);

  /* clean up */
  g_free(shaderSource);

  /* check for errors */
  GLint compiled = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    /* retrieve error buffer size. */
    GLint buf_len, err_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_len);

    gchar *log = (char*)g_malloc((buf_len + 1) * sizeof(char));
    /* retrieve gl error */
    glGetShaderInfoLog(shader, buf_len, &err_len, log);
    log[buf_len] = '\0';
    ERROR("Compilation failed:\n%s\nIn shader: %s", log, fpath);
    g_free(log);

    return 0;
  }

  return shader;
}

shader_program_t shader_create_and_link_program(const char *vertex_shader_fpath, const char *frag_shader_fpath)
{
  shader_program_t shader_program = {0, 0, 0};

  shader_program.vertex_shader = shader_create(vertex_shader_fpath, GL_VERTEX_SHADER);
  if (!shader_program.vertex_shader) {
    ERROR("Video vertex shader could not be compiled");
    return shader_program;
  }

  shader_program.frag_shader = shader_create(frag_shader_fpath, GL_FRAGMENT_SHADER);
  if (!shader_program.frag_shader) {
    ERROR("Video frag shader could not be compiled");
    return shader_program;
  }

  shader_program.program = glCreateProgram();
  glAttachShader(shader_program.program, shader_program.vertex_shader);
  glAttachShader(shader_program.program, shader_program.frag_shader);
  glLinkProgram(shader_program.program);

  /* check if linking succeeded */
  GLint linked = 0;
  glGetProgramiv(shader_program.program, GL_LINK_STATUS, &linked);
  if (!linked) {
    /* retrieve error buffer size. */
    GLint buf_len, err_len;
    glGetProgramiv(shader_program.program, GL_INFO_LOG_LENGTH, &buf_len);

    char *log = (gchar*)g_malloc((buf_len + 1) * sizeof(char));
    /* retrieve gl error */
    glGetProgramInfoLog(shader_program.program, buf_len, &err_len, log);
    log[buf_len] = '\0';
    ERROR("Linking failed:\n%s\nIn shader: %s", log, vertex_shader_fpath);
    g_free(log);

    shader_program.program = 0;
  }

  return shader_program;
}

shader_program_t shader_create_program(const char *shader_name)
{
  if (eglGetCurrentContext() == EGL_NO_CONTEXT) { // TODO Is this function call inefficient?
    ERROR("No EGL context found, call this function when EGL has been initialized");
    return (shader_program_t) {};
  }

  gsize length = strlen(shader_name) + 6; // 5 for extension and 1 for \0

  char *vertex_shader = (gchar *)g_malloc(length);
  char *frag_shader = (gchar *)g_malloc(length);
  g_stpcpy(g_stpcpy(vertex_shader, shader_name), ".vert");
  g_stpcpy(g_stpcpy(frag_shader, shader_name), ".frag");

  shader_program_t shader = shader_create_and_link_program(vertex_shader, frag_shader);
  g_free(vertex_shader);
  g_free(frag_shader);
  return shader;
}

void shader_destroy_program(shader_program_t shader_program)
{
  glDeleteShader(shader_program.vertex_shader);
  glDeleteShader(shader_program.frag_shader);
  glDeleteProgram(shader_program.program);
}
