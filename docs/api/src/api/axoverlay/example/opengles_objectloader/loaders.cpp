/*
 * Copyright (c) 2018 Axis Communications AB.
 */

#include <stdio.h>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <libgen.h>

#include "loaders.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <syslog.h>
#include "gl_example_errors.h"
#include <glm/gtx/normal.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define D(x) if (0) { x; }

static std::map<std::string, GLuint> textures;

static glm::vec3
fetch(const std::vector<float> &values, int index, int components, const glm::vec3 &fallback) {
  if (index < 0) {
    index = values.size()/components + index;
  }
  if ((unsigned int)index > values.size()/components) {
    return fallback;
  }
  float data[3] = {0.0f, 0.0f, 0.0f};
  int offset = index*components;
  for (int i = 0; i<components; ++i) {
    data[i] = values[offset + i];
  }
  return (glm::vec3(data[0], data[1], data[2]));
}

static GLuint
loadTexture(std::vector<tinyobj::material_t> materials, const char *filename)
{
  GError *error = NULL;
  GLuint texture_id = 0;

  /* Append `default` material */
  materials.push_back(tinyobj::material_t());

  for (size_t i = 0; i < materials.size(); i++) {
    D(printf("material[%d].diffuse_texname = %s\n", int(i),
           materials[i].diffuse_texname.c_str()));
  }

  /* Load diffuse textures */
  {
    for (size_t m = 0; m < materials.size(); m++) {
      tinyobj::material_t* mp = &materials[m];

      if (mp->diffuse_texname.length() > 0) {
        // Only load the texture if it is not already loaded
        if (textures.find(mp->diffuse_texname) == textures.end()) {
          int w, h;
          int comp;
          char texture_name[100];

          std::string texture_filename = mp->diffuse_texname;
          memset(texture_name, 0, 100);
          strcpy(texture_name, "/tmp/");
          strcat(texture_name, texture_filename.c_str());


          unsigned char* image =
            stbi_load(texture_name, &w, &h, &comp, STBI_rgb);

          if (!image) {
            D(printf("Unable to load texture: %s\n", texture_filename.c_str()));
            exit(1);
          }

          D(printf("Load texture %s w = %d h = %d comp = %d\n", texture_name, w, h, comp));

          // Convert BMP from BGR to RGB format (opengles2 supports only RGB)
          for (int i = 0; i < w * h; i++) {
            char r = image[i * 3];
            image[i * 3] = image[i * 3 + 2];
            image[i * 3 + 2] = r;
          }

          glActiveTexture(GL_TEXTURE1);
          glGenTextures(1, &texture_id);
          check_gl_error(&error);
          glBindTexture(GL_TEXTURE_2D, texture_id);
          check_gl_error(&error);
          if (comp == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, image);
          } else if (comp == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, image);
          } else {
            assert(0);
          }
          check_gl_error(&error);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
          check_gl_error(&error);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          check_gl_error(&error);
          stbi_image_free(image);
          textures.insert(std::make_pair(mp->diffuse_texname, texture_id));
        }
      }
    }
  }
  return texture_id;
}


int
loadOBJ(const char *path,
    std::vector<glm::vec3> &out_vertices,
    std::vector<glm::vec3> &out_uvs,
    std::vector<glm::vec3> &out_normals,
    GLuint *texture_param)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string err;
  std::string warn;
  glm::vec3 temp_vertices;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path);

  if (!ret) {
    fprintf(stderr, "Failed to load %s: %s\n",
        path, err.c_str());
    return 0;
  }

  if (shapes.size() != 1) {
    fprintf(stderr, "Expected %s to contain exactly one shape, but was %zu\n",
        path, shapes.size());
    return 0;
  }

  out_vertices.clear();
  out_uvs.clear();
  out_normals.clear();

  size_t index_offset = 0;

  /* For each face */
  for (size_t f = 0; f < shapes[0].mesh.num_face_vertices.size(); f++) {
    size_t fnum = shapes[0].mesh.num_face_vertices[f];

    if (fnum != 3) {
      fprintf(stderr, "Expected all faces to be triangles but face %zu has %zu vertices\n",
          f, fnum);
      return 0;
    }

    for (size_t v = 0; v < fnum; v++) {
      temp_vertices = fetch(attrib.vertices, shapes[0].mesh.indices[index_offset + v].vertex_index, 3, (glm::vec3){0,0,0});
      out_vertices.push_back(temp_vertices);
    }

    for (size_t v = 0; v < fnum; v++) {
      out_uvs.push_back(fetch(attrib.texcoords, shapes[0].mesh.indices[index_offset + v].texcoord_index, 2, (glm::vec3){0,0,0}));
    }

    glm::vec3 triangleNormal = glm::triangleNormal(out_vertices[out_vertices.size()-3], out_vertices[out_vertices.size()-2],
                                                   out_vertices[out_vertices.size()-1]);
    for (size_t v = 0; v < fnum; v++) {
      out_normals.push_back(fetch(attrib.normals, shapes[0].mesh.indices[index_offset + v].normal_index, 3, triangleNormal));
    }

    index_offset += fnum;
  }

  size_t n = out_vertices.size() / 3;

  D(printf("Number of triangles: %zu\n", n));


  *texture_param = loadTexture(materials, path);


  return n;
}






