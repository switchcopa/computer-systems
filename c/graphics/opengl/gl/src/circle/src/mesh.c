#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <glad/glad.h>

#include "mesh.h"

Mesh create_mesh(Vertex *vertices, size_t n, MeshManager *mesh_manager)
{
    Mesh mesh;
    mesh.vertex_count = n;

    glGenVertexArrays(1, &mesh.VAO);
    glGenBuffers(1, &mesh.VBO);
    glBindVertexArray(mesh.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
    glBufferData(GL_ARRAY_BUFFER, n * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    mesh_manager->meshes[mesh_manager->meshp++] = mesh;
    return mesh;
}

void mesh_draw(const Mesh *mesh, GLenum type)
{
    glBindVertexArray(mesh->VAO);
    glDrawArrays(type, 0, mesh->vertex_count);
}

MeshManager *mesh_manager_create(void)
{
    MeshManager *mm = malloc(sizeof(MeshManager));
    mm->meshes = malloc(sizeof(Mesh) * MAX_MESHES);
    mm->meshp = 0;
    if (!mm || !mm->meshes)
    {
        fprintf(stderr, "failed to init meshes\n");
        exit(EXIT_FAILURE);
        return NULL;
    }

    return mm;
}

void mesh_manager_cleanup(MeshManager *mesh_manager)
{
    while (mesh_manager->meshp > 0)
    {
        glDeleteVertexArrays(1, &mesh_manager->meshes[mesh_manager->meshp].VAO);
        glDeleteBuffers(1, &mesh_manager->meshes[mesh_manager->meshp].VBO);
    }

    free(mesh_manager->meshes);
    free(mesh_manager);
    mesh_manager = NULL;
}
