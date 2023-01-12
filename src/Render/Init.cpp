#include "init.h"
#include "Updates.h"
#include "ubiq.h"

GLuint g_fa;
GLuint g_fao;
GLuint g_fai;
int g_vertexCount;


static float face[] =
{
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f

};

static unsigned int indices[] =
{
    0, 2, 1,
    0, 3, 2
};

double someFunc(int i, double j)
{
    return (double)i + j;
}

void RenderInit()
{
    glGenVertexArrays(1, &g_fao);
    glBindVertexArray(g_fao);
    glEnableVertexArrayAttrib(g_fao, 1);


    glGenBuffers(1, &g_fa);
    glBindBuffer(GL_ARRAY_BUFFER, g_fa);
    glBufferData(GL_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

    glGenBuffers(1, &g_fai);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_fai);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);


    g_vertexCount = ARRAYLENGTH(indices, int);

}