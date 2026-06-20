#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

unsigned int compile_shader(const char *src, GLenum type);
unsigned int create_shader_program(const char *vsf, const char *fsf);
void shader_program_report_error(GLuint obj, GLenum type);

#endif
