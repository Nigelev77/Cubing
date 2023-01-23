#include "init.h"
#include "Updates.h"
#include "ubiq.h"
#include <iostream>
#include "Toolbox/Shaders.h"

GLuint g_fa;
GLuint g_fao;
GLuint g_fai;
int g_vertexCount;


static float face[] =
{
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f

};

static unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3
};

double someFunc(int i, double j)
{
    return (double)i + j;
}

void RenderInit()
{
    std::cout << "Initing Render" << '\n';
    glGenVertexArrays(1, &g_fao);
    glBindVertexArray(g_fao);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &g_fa);
    glBindBuffer(GL_ARRAY_BUFFER, g_fa);
    glBufferData(GL_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

    glGenBuffers(1, &g_fai);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_fai);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);


    g_vertexCount = ARRAYLENGTH(indices, int);


    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);

    //ShaderInit
    std::cout << "Initing Shaders" << "\n";
    g_CubeShader = CreateShader("../src/Render/Shaders/cube.vert", "../src/Render/Shaders/cube.frag");
    if (g_CubeShader.prog == UINT32_MAX) std::cout << "Shader creation failed" << "\n";
}