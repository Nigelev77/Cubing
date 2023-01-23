#include <iostream>
#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include "Toolbox/Shaders.h"
#include "gtc/matrix_transform.hpp"


#include "CubeRender.h"

static glm::vec3 s_camPos{ 0.0f, 0.0f, 0.0f };
static glm::vec3 s_camRots{ -90.0f, 0.0f, 0.0f };
static glm::vec3 s_camFront{ 0.0f, 0.0f, -1.0f };
static glm::vec3 s_camRight{ 1.0f, 0.0f, 0.0f };
static glm::mat4 s_viewMat = glm::mat4(1.0f);
static glm::mat4 s_projMat = glm::perspective(45.0f, 16.0f / 9.0f, 0.25f, 250.0f);

bool changedDim = false;
#include "IO_Game_interface.h"
void UpdateInputs(INPUTS* newInputs)
{
    bool changedAlready = false;
    if (newInputs->keys[GLFW_KEY_W].isPressed) s_camPos += 0.001f * s_camFront;
    if (newInputs->keys[GLFW_KEY_S].isPressed) s_camPos -= 0.001f * s_camFront;
    if (newInputs->keys[GLFW_KEY_A].isPressed) s_camPos -= 0.001f * s_camRight;
    if (newInputs->keys[GLFW_KEY_D].isPressed) s_camPos += 0.001f * s_camRight;
    if (newInputs->keys[GLFW_KEY_Q].isPressed) s_camPos.y -= 0.001f;
    if (newInputs->keys[GLFW_KEY_SPACE].isPressed) s_camPos.y += 0.001f;
    if (newInputs->keys[GLFW_KEY_G].isPressed)
    {
        s_camPos = { 0.0f, 0.0f, 0.0f };
        s_camRots = { 0.0f, 0.0f, 0.0f };
    }

    INPUT_STATE& one = newInputs->keys[GLFW_KEY_1];
    INPUT_STATE& two = newInputs->keys[GLFW_KEY_2];

    if (one.isPressed && !two.isPressed && !changedDim)
    {
        g_dim++;
        changedDim = true;
    }



    if (!one.isPressed && two.isPressed && !changedDim)
    {
        g_dim--;
        if (g_dim == 0) g_dim++;
        changedDim = true;
    }

    if (!one.isPressed && !two.isPressed) changedDim = false;


    if (newInputs->keys[GLFW_KEY_C].isPressed) std::cout << "Key pressed!\n";
    if (newInputs->keys[GLFW_KEY_E].isPressed) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (newInputs->keys[GLFW_KEY_R].isPressed) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (newInputs->keys[GLFW_KEY_T].isPressed)
    {
        glPointSize(10.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    return;
}

#define CLAMP(v, l, u) v = v > u ? v-u : v < l ? v + u : v
void UpdateMouse(MOUSE_INPUTS* newMouse)
{
    s_camRots.x += newMouse->dx;
    s_camRots.y -= newMouse->dy;
    CLAMP(s_camRots.x, 0.0F, 360.0f);
    CLAMP(s_camRots.y, 0.0f, 360.0f);
    s_camFront.x = glm::cos(glm::radians(s_camRots.x)) * glm::cos(glm::radians(s_camRots.y));
    s_camFront.y = glm::sin(glm::radians(s_camRots.y));
    s_camFront.z = glm::sin(glm::radians(s_camRots.x)) * glm::cos(glm::radians(s_camRots.y));
    s_camFront = glm::normalize(s_camFront);
    s_camRight = glm::normalize(glm::cross(s_camFront, glm::vec3(0.0f, 1.0f, 0.0f)));
}

extern INPUTS g_inputs;

void RenderUpdate(double delta)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::cout << delta << "\n";
    UpdateInputs(&g_inputs);

    LoadShader(g_CubeShader.prog);

    glm::mat4 u_MVP = glm::mat4(1.0f);
    // s_viewMat = glm::mat4(1.0f);
    // s_viewMat = glm::rotate(s_viewMat, glm::radians(s_camRots.y), glm::vec3(1.0f, 0.0f, 0.0f));
    // s_viewMat = glm::rotate(s_viewMat, glm::radians(s_camRots.x), glm::vec3(0.0f, 1.0f, 0.0f));
    // s_viewMat = glm::rotate(s_viewMat, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // s_viewMat = glm::translate(s_viewMat, -s_camPos);
    glm::vec3 up{};

    up = glm::normalize(glm::cross(s_camRight, s_camFront));
    s_viewMat = glm::lookAt(s_camPos, s_camPos + s_camFront, up);
    u_MVP = s_projMat * s_viewMat;
    //Set uniforms
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");


    // glBindVertexArray(g_fao);
    // glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(g_fao);
    CalculateAndRender(s_projMat, s_viewMat);
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

}