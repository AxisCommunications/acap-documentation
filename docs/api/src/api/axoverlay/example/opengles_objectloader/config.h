/*
 * Copyright (c) 2019 Axis Communications AB.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "mesh.h"
#include <glib.h>
#include <glm/mat4x4.hpp>

#include <vector>


struct position {
  int sec;
  int usec;
  int flip;
  float pan;
  float tilt;
  float hfov;
  float vfov;
};

struct object {
  float alpha;
  int lightdir;
  int light_static; // 1 light static, 0 light rotates with object
  char name[50];
  Mesh mesh;
  std::vector< glm::vec3 > vert;
  std::vector< glm::vec3 > uvs;
  std::vector< glm::vec3 > normal;
};

struct config{
  bool enabled;
  struct object *object;
  int bronze;
  float targ;
  float camera_position_y;
  int camera_view;
  float pos;
  float scale;
  int lock;
  float calib_north;
  struct position position;
  glm::mat4 projMatrix;
};

struct config *get_config(void);
void config_init(GMainContext *context, const char *object_name, float pan,
                 float tilt, float scale);
#endif