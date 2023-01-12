#include "Updates.h"
#include "glad/glad.h"
#include "init.h"


void RenderUpdate(double delta)
{
    glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, nullptr);
}