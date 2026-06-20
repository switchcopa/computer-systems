#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.h"

void glfw_init()
{
    if (!glfwInit())
    {
        fprintf(stderr, "failed to init glfw\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void glfw_init_window(GLFWwindow **window, const char *window_title)
{
    if ((*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, window_title, NULL, NULL)) == NULL)
    {
        fprintf(stderr, "failed to init window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void glad_load_gl()
{
    if (!gladLoadGLLoader((GLADloadproc)
                          glfwGetProcAddress))
    {
        fprintf(stderr, "failed to init GLAD\n");
        exit(EXIT_FAILURE);
    }
}
