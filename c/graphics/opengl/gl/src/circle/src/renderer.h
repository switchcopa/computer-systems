#ifndef RENDERER_H
#define RENDERER_H

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#include <glad/glad.h>

void glfw_init(void);
void glfw_init_window(GLFWwindow **window, const char *window_title);
void glad_load_gl(void);

#endif
