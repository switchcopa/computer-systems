#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"
#include "mesh.h"
#include "shader.h"
#include "../include/meshes.h"

#include <stdlib.h>

int main(void)
{
    GLFWwindow *window = NULL;
    const char *window_title = "simple GLFW window";

    glfw_init();
    glfw_init_window(&window, window_title);

    glfwMakeContextCurrent(window);
    glad_load_gl();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    MeshManager *mesh_manager = mesh_manager_create();

    extern Vertex triangle[];
    extern const size_t triangle_count;
    Mesh triangle_mesh = create_mesh(triangle, triangle_count, mesh_manager);

    unsigned int shader_program = create_shader_program("shaders/vertex.glsl", "shaders/fragment.glsl");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);

        mesh_draw(&triangle_mesh, GL_TRIANGLES);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    mesh_manager_cleanup(mesh_manager);
    glfwTerminate();

    return EXIT_SUCCESS;
}
