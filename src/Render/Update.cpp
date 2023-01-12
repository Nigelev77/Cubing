#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include <iostream>


void RenderUpdate(double delta)
{
    glBindVertexArray(g_fao);
    glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, 0);
}