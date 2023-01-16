#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include <iostream>
#include "Toolbox/Shaders.h"
#include "gtc/matrix_transform.hpp"


static glm::vec3 s_camPos{ 0.0f, 1.0f, 2.0f };
static glm::mat4 s_viewMat = glm::mat4(1.0f);
static glm::mat4 s_projMat = glm::perspective(45.0f, 16.0f / 9.0f, 0.5f, 250.0f);

void RenderUpdate(double delta)
{
    static float changeY = 0.001f;
    static float changeX = 0.002f;
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    LoadShader(g_CubeShader.prog);

    glm::mat4 u_MVP = glm::mat4(1.0f);
    if (s_camPos.y > 2.0f || s_camPos.y < 0.0f) changeY *= -1;
    if (s_camPos.x > 2.0f || s_camPos.x < 0.0f) changeX *= -1;
    s_camPos.x += changeX;
    s_camPos.y += changeY;
    s_viewMat = glm::mat4(1.0f);
    s_viewMat = glm::rotate(s_viewMat, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    s_viewMat = glm::translate(s_viewMat, -s_camPos);
    u_MVP = s_projMat * s_viewMat;
    //Set uniforms
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");


    glBindVertexArray(g_fao);
    glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, 0);
}