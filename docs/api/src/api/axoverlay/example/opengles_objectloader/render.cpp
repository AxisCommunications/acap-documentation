/*
 * Copyright (C) 2019, Axis Communications AB, LUND, SWEDEN
 */

#include "render.h"
#include "config.h"
#include "shaders.h"

#include "EGL/egl.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <math.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "gl_example_errors.h"
#include "loaders.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/transform.hpp>

GLuint shader = 0;

static void
init_opengles()
{
  GError *error = NULL;

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  check_gl_error(&error);
  glEnable(GL_CULL_FACE);
  glClearColor(0, 0, 0, 0);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClear(GL_COLOR_BUFFER_BIT );
  glClearDepthf(1.0);
  check_gl_error(&error);
  glActiveTexture(GL_TEXTURE0);
}

static void
load_object(struct config* config)
{
  char str[100];
  GLuint texture;

  memset(str,0, 100);
  strcpy(str, "/tmp/");
  strcat(str, config->object->name);
  strcat(str, ".obj");
  int ret = loadOBJ(str, config->object->vert, config->object->uvs, config->object->normal, &texture);
  if (!ret)
    printf("Could not open file %s\n", str);

  config->object->mesh.setTexture(texture);
}

static void
init_projection_matrix(float fov, float far, float near, int w, int h, struct config *config)
{
  config->projMatrix[0][0] = cosf( fov ) / sinf( fov );
  config->projMatrix[1][1] = config->projMatrix[0][0] * (w/h) ;
  config->projMatrix[2][2] = -(far+near)/(far-near);
  config->projMatrix[2][3] = -1.0f;
  config->projMatrix[3][2] = (-2*far*near)/(far-near);
}

static void
init_light_projection(struct config* config)
{
  glm::vec4 light_white = glm::vec4(0.9, 0.9, 0.8, 1.0); //White light
  glm::vec4 light_bronze = glm::vec4(0.2, 0.4, 0.7, 1.0); //Bronze light

  /*First shader used for objects*/
  shader_program_t shaderProgram = shader_create_program("/tmp/shader");
  shader = shaderProgram.program;

  config->object->mesh.setShader(shader);

  if (config->bronze == 1) {
    light_bronze[3] = config->object->alpha;
    config->object->mesh.setLightColor(light_bronze);
  }
  else {
    light_white[3] = config->object->alpha;
    config->object->mesh.setLightColor(light_white);
  }

  config->object->mesh.setAlpha(config->object->alpha);
  config->object->mesh.setModelToWorldLight(config->object->light_static);
}

static void
init_light_direction(struct config* config)
{
  /*Define some light directions*/
  glm::vec3 light_direction = glm::vec3(-2.0, -1.0, -1.0);
  glm::vec3 light_direction_below = glm::vec3(0.0, 1.0, 0.0);
  glm::vec3 light_direction_above = glm::vec3(0.0, -1.0, -1.0);
  glm::vec3 light_direction_zoom = glm::vec3(-2.0, -1.0, -2.0);

  glm::vec3 light_dir = glm::vec3(0.0, 0.0, 0.0);

  if(config->object->lightdir == 1){
    light_dir = light_direction_below;
  }else if(config->object->lightdir == 2){
    light_dir = light_direction_zoom;
  }else if(config->object->lightdir == 3){
    light_dir = light_direction_above;
  }else{
    light_dir = light_direction;
  }

  config->object->mesh.setLightDirection(light_dir);
}

void
render_init(struct config* config)
{
  glm::vec3 camera_position = glm::vec3(0.0f, config->camera_position_y, 0.0f);
  glm::vec3 target = glm::vec3(0.0f, 0.0f, config->targ);

  init_opengles();

  init_projection_matrix(0.5, 20, 0.1, 1024, 1024, config);

  load_object(config);

  config->object->mesh.createMesh(config->object->vert,config->object->uvs,config->object->normal);

  init_light_projection(config);

  init_light_direction(config);

  if(config->camera_view == 1) {
    config->object->mesh.setCamera(camera_position, target);
  }

  config->object->mesh.setProjection(config->projMatrix);
}

void
render(struct config* config)
{
  float pan_input;
  float tilt_input;
  float pan_output;
  float tilt_output;
  float tilt_ref = 1.0f;
  float input_north = 1.0f;
  float calib_north = config->calib_north;
  float tilt;
  float pan ;

  GError *error = NULL;

  glm::mat4 mat_x = glm::mat4(1.0);
  glm::mat4 mat_y = glm::mat4(1.0);

  glm::mat4 modelToWorld = glm::mat4(1.0);

  if (!config->enabled) {
    return;
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  check_gl_error(&error);
  glDepthFunc(GL_LEQUAL);

  pan_input = config->position.pan;
  tilt_input = config->position.tilt;

  if (isnan(tilt_input) || isnan(pan_input)){
    tilt_input = tilt_ref;
    pan_input = input_north;
  }

  tilt_ref = 1.0;
  calib_north = input_north;


  if (config->position.flip == 1){
    tilt_ref = tilt_ref-0.5;
    tilt = tilt_input-tilt_ref;
    calib_north = input_north-0.5;
  }else{
    tilt = tilt_ref-tilt_input;
  }


  pan = calib_north-pan_input; /* ok when tilted since pan data fliped */
  if(tilt>0.175 && config->camera_view && config->lock){
    /* Quick fix to make object look good when looking from above*/
    tilt = 0.175;
  }

  pan_output = -1* (pan) * 2 * M_PI;
  tilt_output = -1* tilt* 2*M_PI;

  /* scale and rotation matrix x-axis */
  mat_x = glm::scale(mat_x, glm::vec3(config->scale, config->scale, config->scale));
  mat_x = glm::rotate(mat_x, tilt_output, glm::vec3(1, 0, 0));

  /* rotate around y-axis */
  mat_y = glm::rotate(mat_y, pan_output, glm::vec3(0, 1, 0));

  modelToWorld = mat_x * mat_y;

  config->object->mesh.setModelToWorld(modelToWorld);

  config->object->mesh.renderMesh();
}
