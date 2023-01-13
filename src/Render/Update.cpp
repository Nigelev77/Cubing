#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include <iostream>
#include "Toolbox/Shaders.h"


void RenderUpdate(double delta)
{
    glBindVertexArray(g_fao);
    LoadShader(g_CubeShader.prog);
    glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, 0);
}