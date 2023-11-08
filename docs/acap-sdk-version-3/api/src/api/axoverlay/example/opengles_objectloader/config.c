/*
 * Copyright (c) 2019 Axis Communications AB.
 */

#include "config.h"

#include <stdio.h>
#include <string.h>
#include <pthread.h>


static struct config config;

static void
object_init(struct config* config_param, const char *object_name)
{
  memset(config_param->object->name, 0 , 50);
  memcpy(config_param->object->name, object_name, 50);
  config_param->object->lightdir = 0;
  config_param->object->alpha = 1.0f;
  config_param->object->light_static = 1; // 1 light static, 0 light rotates with object
}

void
config_init(GMainContext *context, const char *object_name, float pan,
            float tilt, float scale)
{
  struct config* local_config = get_config();

  local_config->object = (object *)g_malloc(sizeof(struct object));

  if (object_name != NULL) {
    object_init(local_config, object_name);
  }

  local_config->bronze = 0;
  local_config->targ = -2.0f;
  local_config->camera_position_y = -1.0f;
  local_config->camera_view = 0;
  local_config->pos = -2.0f;
  local_config->scale = scale;
  local_config->lock = 0;
  local_config->calib_north = 1.0f;
  local_config->enabled = true;

  local_config->position.pan = pan;
  local_config->position.tilt = tilt;

  local_config->projMatrix = glm::mat4(1.0);
}

struct config *get_config(void)
{
  return &config;
}
