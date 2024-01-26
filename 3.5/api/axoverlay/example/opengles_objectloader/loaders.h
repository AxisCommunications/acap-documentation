/*
 * Copyright (c) 2018 Axis Communications AB.
 */


#ifndef LOADERS_H
#define LOADERS_H

#include <GLES2/gl2.h>
#include <glm/vec3.hpp>
#include <vector>

/* loads an .obj file */
int loadOBJ(const char *path,
    std::vector<glm::vec3> &out_vertices,
    std::vector<glm::vec3> &out_uvs,
    std::vector<glm::vec3> &out_normals,
    GLuint *texture_param
);

#endif
