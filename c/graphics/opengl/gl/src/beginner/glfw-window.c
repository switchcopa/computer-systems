#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <glad/glad.h> // “A loader that fetches all OpenGL functions from your driver.”
#include <GLFW/glfw3.h> // context: "A GPU state machine allocated for your program."

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
#define BUFFER_SIZE     5000
#define LOG_BUF_SIZE    512
#define MAX_MESHES      128

typedef struct {
    float x;
    float y;
    float z;
} vec3;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} rgba;

typedef struct {
    vec3 pos;
    rgba color;
} Vertex;

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int vertex_count;
} Mesh;

// glfw/glad functions
void glfw_init(void);
void glfw_init_window(GLFWwindow **window, const char *window_title);
void glad_load_gl(void);

// helper functions
ssize_t read_file(char *buffer, const char *filename);

// shader and program functions
unsigned int compile_shader(const char *src, GLenum type);
unsigned int create_shader_program(const char *vsf, const char *fsf);
void shader_program_report_error(GLuint obj, GLenum type);

// mesh and vertices functions
Mesh create_mesh(Vertex *vertices, size_t n, int *meshesp, Mesh *meshes);
void mesh_draw(const Mesh *mesh, GLenum type);
Mesh *meshes_create(void);
void meshes_delete(Mesh *meshes, int meshesp);

Vertex triangle[] =
{
    { { -0.7f,  0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
    { { -0.7f, -0.7f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
    { {  0.7f,  0.0f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f} }
};

Vertex polygon[] = {
    { { 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f, 1.0f, 1.0f} },

    { { 0.0f, 0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
    { { 0.67f, 0.22f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
    { { 0.41f, -0.56f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f} },
    { { -0.41f, -0.56f, 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} },
    { { -0.67f, 0.22f, 0.0f }, {1.0f, 0.0f, 1.0f, 1.0f} },

    { { 0.0f, 0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} }
};

int main(void)
{
    GLFWwindow *window = NULL;
    char *window_title = "simple GLFW window";

    glfw_init();
    glfw_init_window(&window, window_title);

    glfwMakeContextCurrent(window);
    glad_load_gl();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Mesh *meshes = meshes_create();
    if (!meshes)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    int meshesp = 0;
    Mesh triangle_mesh = create_mesh(triangle, sizeof(triangle) / sizeof(Vertex), &meshesp, meshes);
    Mesh polygon_mesh  = create_mesh(polygon,  sizeof(polygon) / sizeof(Vertex), &meshesp, meshes);

    unsigned int shader_program = create_shader_program("vertex-shader.glsl", "fragment-shader.glsl");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_program);

        mesh_draw(&polygon_mesh, GL_TRIANGLE_FAN);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    meshes_delete(meshes, meshesp);
    glfwTerminate();
    return EXIT_SUCCESS;
}

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

ssize_t read_file(char *buffer, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return -1;

    fseek(fp, 0, SEEK_END);
    size_t s = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    ssize_t bytes = fread(buffer, sizeof(char), s, fp);
    if (bytes > 0 && bytes < BUFFER_SIZE - 1)
        buffer[bytes++] = '\0';

    fclose(fp);
    return bytes;
}

unsigned int compile_shader(const char *src, GLenum type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    shader_program_report_error(shader, GL_COMPILE_STATUS);
    return shader;
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

Mesh create_mesh(Vertex *vertices, size_t n, int *meshesp, Mesh *meshes)
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

    meshes[*meshesp++] = mesh;
    return mesh;
}

void mesh_draw(const Mesh *mesh, GLenum type)
{
    glBindVertexArray(mesh->VAO);
    glDrawArrays(type, 0, mesh->vertex_count);
}

Mesh *meshes_create(void)
{
    Mesh *meshes = malloc(sizeof(Mesh) * MAX_MESHES);
    if (!meshes)
    {
        fprintf(stderr, "failed to init meshes\n");
        return NULL;
    }
 
    return meshes;
}

void meshes_delete(Mesh *meshes, int meshesp)
{
    for (int i = 0; i < meshesp; i++)
    {
        glDeleteVertexArrays(1, &meshes[i].VAO);
        glDeleteBuffers(1, &meshes[i].VBO);
    }

    free(meshes);
    meshes = NULL;
}
