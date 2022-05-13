/*
 * 3D Compass
 * Copyright (c) 2018 Axis Communications AB.
 */

#ifndef MESH_H
#define MESH_H

#include <GLES2/gl2.h>

#include <vector>
#include <map>
#include "loaders.h"

#include <iostream>
#include <string>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#ifdef __cplusplus
extern "C" {
#endif

class Mesh {
  public:
  void createMesh(std::vector<glm::vec3> inVert);
  void createMesh(std::vector<glm::vec3> inVert, std::vector<glm::vec3> inUV);
  void createMesh(std::vector<glm::vec3> inVert, std::vector<glm::vec3> inUV,
                  std::vector<glm::vec3> inNormal);
  void renderMesh();

  void setMesh(std::vector<glm::vec3> inVert);
  void setAlpha(GLfloat alpha_in);
  void setLightColor(const glm::vec4 light_color_in);
  void setLightDirection(const glm::vec3 light_in);

  void setShader(GLint locShader);

  void setModelToWorldLight(GLint light_static_in);
  void setColor(glm::vec4 col);
  void setTexture(GLuint texture_param);
  void setModelToWorld(glm::mat4 inMat);
  void setProjection(glm::mat4 inMat);
  void setCamera(glm::vec3 camera_position, glm::vec3 target);


  private:
  glm::vec4 color;
  std::vector<float> alpha;
  glm::vec4 light_color;
  glm::vec3 light_dir;
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> uvs;

  glm::mat4 modelToWorldMatrix;
  glm::mat4 modelToWorldMatrixIT;
  glm::mat4 projMatrix;
  glm::mat4 viewMatrix;


  GLint objShader;
  GLint light_static;
  GLint texture;
};

#ifdef __cplusplus
}
#endif

#endif
