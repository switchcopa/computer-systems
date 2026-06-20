#include <stddef.h>
#include "../include/meshes.h"
#include "mesh.h"

Vertex triangle[] =
{
    { { -0.7f,  0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
    { { -0.7f, -0.7f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
    { {  0.7f,  0.0f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f} }
};

const size_t triangle_count = sizeof(triangle) / sizeof(Vertex);

Vertex polygon[] =
{
    { { 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f, 1.0f, 1.0f} },

    { { 0.0f, 0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} },
    { { 0.67f, 0.22f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f} },
    { { 0.41f, -0.56f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f} },
    { { -0.41f, -0.56f, 0.0f }, {1.0f, 1.0f, 0.0f, 1.0f} },
    { { -0.67f, 0.22f, 0.0f }, {1.0f, 0.0f, 1.0f, 1.0f} },

    { { 0.0f, 0.7f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} }
};

const size_t polygon_count = sizeof(polygon) / sizeof(Vertex);
