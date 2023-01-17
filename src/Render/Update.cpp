#include <iostream>
#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include "Toolbox/Shaders.h"
#include "gtc/matrix_transform.hpp"


#include "CubeRender.h"

static glm::vec3 s_camPos{ 0.0f, 0.0f, 0.0f };
static glm::mat4 s_viewMat = glm::mat4(1.0f);
static glm::mat4 s_projMat = glm::perspective(45.0f, 16.0f / 9.0f, 0.5f, 250.0f);

#include "IO_Game_interface.h"
void UpdateInputs(INPUTS* newInputs)
{

    if (newInputs->keys[GLFW_KEY_W].isPressed) s_camPos.z -= 0.05f;
    if (newInputs->keys[GLFW_KEY_S].isPressed) s_camPos.z += 0.05f;
    if (newInputs->keys[GLFW_KEY_A].isPressed) s_camPos.x -= 0.05f;
    if (newInputs->keys[GLFW_KEY_D].isPressed) s_camPos.x += 0.05f;
    if (newInputs->keys[GLFW_KEY_Q].isPressed) s_camPos.y -= 0.05f;
    if (newInputs->keys[GLFW_KEY_SPACE].isPressed) s_camPos.y += 0.05f;

    if (newInputs->keys[GLFW_KEY_C].isPressed) std::cout << "Key pressed!\n";
    return;
}



void RenderUpdate(double delta)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    LoadShader(g_CubeShader.prog);

    glm::mat4 u_MVP = glm::mat4(1.0f);
    s_viewMat = glm::mat4(1.0f);
    s_viewMat = glm::rotate(s_viewMat, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    s_viewMat = glm::translate(s_viewMat, -s_camPos);
    u_MVP = s_projMat * s_viewMat;
    //Set uniforms
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");


    // glBindVertexArray(g_fao);
    // glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(g_fao);
    CalculateAndRender(s_projMat, s_viewMat);

}