/*
 * 3D Compass
 * Copyright (c) 2018 Axis Communications AB.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>
#include "mesh.h"
#include "loaders.h"
#include "gl_example_errors.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Mesh::createMesh(std::vector<glm::vec3> inVert)
{
  createMesh(inVert, std::vector<glm::vec3>(), std::vector<glm::vec3>());
}

void Mesh::createMesh(std::vector<glm::vec3> inVert, std::vector<glm::vec3> inUV)
{
  createMesh(inVert, inUV, std::vector<glm::vec3>());
}

void Mesh::createMesh(std::vector<glm::vec3> inVert, std::vector<glm::vec3> inUV, std::vector<glm::vec3> inNormal)
{
  // assign base color (purple) to mesh
  color = glm::vec4(1.0, 0.0, 1.0, 1.0);

  light_color = glm::vec4(1.0, 1.0, 1.0, 1.0);

  light_dir = glm::vec3(2.0, 1.0, 2.0);

  // set basic modelView matrix
  modelToWorldMatrix[0] = glm::vec4(0.5, 0.0, 0.0, 0.0);
  modelToWorldMatrix[1] = glm::vec4(0.0, 0.5, 0.0, 0.0);
  modelToWorldMatrix[2] = glm::vec4(0.0, 0.0, 0.5, 0.0);
  modelToWorldMatrix[3] = glm::vec4(0.0, 0.0, 0.0, 1.0);

  // set basic projection Matrix
  // set basic camera position matrix
  projMatrix = glm::mat4(1.0);
  viewMatrix = glm::mat4(1.0);

  // set imported values
  vertices = inVert;
  normals = inNormal;
  uvs = inUV;
}

void Mesh::setTexture(GLuint texture_param)
{
  if (!texture_param) {
    printf("Couldn't load texture\n");
  }
  else {
    texture = texture_param;
  }
}

void Mesh::setShader(GLint locShader)
{
  objShader = locShader;
}

void Mesh::setModelToWorldLight(GLint light_static_in)
{
  light_static = light_static_in; // 1 if static 0 if rotates
}

void Mesh::setModelToWorld(glm::mat4 inMat)
{
  modelToWorldMatrix = inMat;

  glm::mat4 temp = glm::inverse(modelToWorldMatrix);

  modelToWorldMatrixIT = glm::transpose(temp);
}

void Mesh::setAlpha(GLfloat alpha_in)
{
  alpha.clear();
  alpha.push_back(alpha_in);
}
void Mesh::setLightColor(const glm::vec4 light_color_in)
{
  light_color = light_color_in;
}
void Mesh::setLightDirection(const glm::vec3 light_in)
{
  light_dir = light_in;
}

void Mesh::setProjection(glm::mat4 inMat)
{
  projMatrix = inMat;
}

void Mesh::renderMesh()
{
  GError *error = NULL;
  // determine what shader to use
  glUseProgram(objShader);
  // vertex stuff
  GLint locVertices = glGetAttribLocation(objShader, "in_vertex"); // might not need to be done every time
  glEnableVertexAttribArray(locVertices);
  glVertexAttribPointer(locVertices, 3, GL_FLOAT, GL_FALSE, 0, &vertices[0]);
  check_gl_error(&error);
  // uv
  if (uvs.size() > 0)
  {
    GLint locTexcoord = glGetAttribLocation(objShader, "in_texcoor"); // might not need to be done every time
    glEnableVertexAttribArray(locTexcoord);
    glVertexAttribPointer(locTexcoord, 3, GL_FLOAT, GL_FALSE, 0, &uvs[0]);

    // texture stuff
    glActiveTexture(GL_TEXTURE2);
    // Bind texture to active unit.
    glBindTexture(GL_TEXTURE_2D, texture);
    GLint locSampler = glGetUniformLocation(objShader, "in_sampler");
    //unit = 2, send this to shader
    glUniform1i(locSampler, 2);
    check_gl_error(&error);
  }
  // normals
  if (normals.size() > 0)
  {
    GLint locNormals = glGetAttribLocation(objShader, "in_normal");
    if (locNormals != -1)
    {
      glEnableVertexAttribArray(locNormals);
      glVertexAttribPointer(locNormals, 3, GL_FLOAT, GL_FALSE, 0, &normals[0]);
      check_gl_error(&error);
    }
  }

  GLint locLight = glGetUniformLocation(objShader, "in_light");
  if (locLight != -1)
  {
    glUniform3f(locLight, light_dir[0], light_dir[1], light_dir[2]);
    check_gl_error(&error);
  }
  GLint locLightColor = glGetUniformLocation(objShader, "lightColor");
  if (locLightColor != -1)
  {
    glUniform4f(locLightColor, light_color[0], light_color[1], light_color[2], light_color[3]);
  }

  check_gl_error(&error);

  GLint locAlpha = glGetUniformLocation(objShader, "in_alpha");
  glUniform1fv(locAlpha, 1, &alpha[0]);
  check_gl_error(&error);
  // modelView matrix
  GLint locModelToWorldMat = glGetUniformLocation(objShader, "in_modelToWorldMatrix");
  glUniformMatrix4fv(locModelToWorldMat, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));
  check_gl_error(&error);

  GLint locModelToWorldITMat = glGetUniformLocation(objShader, "in_modelToWorldMatrixIT");
  glUniformMatrix4fv(locModelToWorldITMat, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrixIT));
  check_gl_error(&error);


  GLint locLightModelToWorldMat = glGetUniformLocation(objShader, "in_lightModelToWorldMatrix");
  if (!light_static)
  {
    glUniformMatrix4fv(locLightModelToWorldMat, 1, GL_FALSE, glm::value_ptr(modelToWorldMatrix));
  }
  else
  {
    glm::mat4 eyemat = glm::mat4(1.0);
    glUniformMatrix4fv(locLightModelToWorldMat, 1, GL_FALSE, glm::value_ptr(eyemat));
  }
  check_gl_error(&error);

  // projection Matrix
  GLint locProjMat = glGetUniformLocation(objShader, "in_projMatrix");
  glUniformMatrix4fv(locProjMat, 1, GL_FALSE, glm::value_ptr(projMatrix));
  check_gl_error(&error);

  // color
  GLint locColor = glGetUniformLocation(objShader, "in_color");
  glUniform4fv(locColor, 1, glm::value_ptr(color));
  check_gl_error(&error);

  GLint viewMat = glGetUniformLocation(objShader, "in_viewMatrix");
  glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  check_gl_error(&error);

  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  glUseProgram(objShader);
}

void Mesh::setMesh(std::vector<glm::vec3> inVert)
{
  vertices = inVert;
}

void Mesh::setColor(glm::vec4 col)
{
  color = col;
}

void Mesh::setCamera(glm::vec3 camera_position, glm::vec3 target)
{
  glm::vec3 upDir = glm::vec3(0, 1, 0);
  viewMatrix = glm::lookAt(camera_position, target, upDir);
}
