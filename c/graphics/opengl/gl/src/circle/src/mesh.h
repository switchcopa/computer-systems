#ifndef MESH_H
#define MESH_H

#include <stddef.h>
#include <glad/glad.h>
#include "math.h"

#define MAX_MESHES 128

typedef struct {
    vec3 pos;
    rgba color;
} Vertex;

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int vertex_count;
} Mesh;

typedef struct {
    Mesh *meshes;
    int meshp;
} MeshManager;

Mesh create_mesh(Vertex *vertices, size_t n, MeshManager *mesh_manager);
void mesh_draw(const Mesh *mesh, GLenum type);
MeshManager *mesh_manager_create(void);
void mesh_manager_cleanup(MeshManager *mesh_manager);

#endif
