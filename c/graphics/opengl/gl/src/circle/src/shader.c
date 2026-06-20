#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "tools.h"
#include "shader.h"

unsigned int compile_shader(const char *src, GLenum type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    shader_program_report_error(shader, GL_COMPILE_STATUS);
    return shader;
}

unsigned int create_shader_program(const char *vsf, const char *fsf)
{
    char vssrc[BUFFER_SIZE];
    char fssrc[BUFFER_SIZE];
    read_file(vssrc, vsf);
    read_file(fssrc, fsf);

    unsigned int vs = compile_shader(vssrc, GL_VERTEX_SHADER),
                 fs = compile_shader(fssrc, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    shader_program_report_error(program, GL_LINK_STATUS);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

void shader_program_report_error(GLuint obj, GLenum pname)
{
    int success;
    if (pname == GL_COMPILE_STATUS)
        glGetShaderiv(obj, pname, &success);
    else if (pname == GL_LINK_STATUS)
        glGetProgramiv(obj, pname, &success);
    else
        return;

    if (!success)
    {
        char log[LOG_BUF_SIZE];
        glGetShaderInfoLog(obj, LOG_BUF_SIZE, NULL, log);
        fprintf(stderr, "Shader compile or program link error:\n%s\n", log);
        exit(EXIT_FAILURE);
    }
}
