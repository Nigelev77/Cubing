#include <iostream>
#include "Updates.h"
#include "glad/glad.h"
#include "init.h"
#include "Toolbox/Shaders.h"
#include "gtc/matrix_transform.hpp"
#include <string>


#include "CubeRender.h"
#include "FontRender.h"
static glm::vec3 s_camPos{ 0.0f, 0.0f, 0.0f };
static glm::vec3 s_camRots{ -90.0f, 0.0f, 0.0f };
static glm::vec3 s_camFront{ 0.0f, 0.0f, -1.0f };
static glm::vec3 s_camRight{ 1.0f, 0.0f, 0.0f };
static glm::mat4 s_viewMat = glm::mat4(1.0f);
static glm::mat4 s_projMat = glm::perspective(45.0f, 16.0f / 9.0f, 0.01f, 250.0f);

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

static bool clicked = false;


void UpdateMouse(MOUSE_INPUTS* newMouse)
{
    if (clicked) return;
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

struct MouseDrag
{
    double lastX, lastY;
    double dx, dy;
};

static MouseDrag mousebuttonDrag[2];

#include "glm/gtc/quaternion.hpp"
extern glm::quat cubeOrientation;
glm::vec3 cubeRight{ 1.0f, 0.0f, 0.0f };
glm::vec3 cubeUp{ 0.0f, 1.0f, 0.0f };


void UpdateMouseButton(MOUSE_INPUTS* newMouse)
{
    static glm::quat currentOrientation;
    static bool first = true;
    if (newMouse->buttons[0].isHeld && first)
    {
        first = false;
        mousebuttonDrag[0].lastX = newMouse->x;
        mousebuttonDrag[0].lastY = newMouse->y;
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        MouseDrag& button = mousebuttonDrag[i];
        if (newMouse->buttons[i].isHeld)
        {

            button.dx = newMouse->x - button.lastX;
            button.dy = newMouse->y - button.lastY;
            button.lastX = newMouse->x;
            button.lastY = newMouse->y;
        }
    }
    if (newMouse->buttons[0].isHeld)
    {
        clicked = true;
        glm::vec3 dxyz{ glm::radians(mousebuttonDrag[0].dy), glm::radians(mousebuttonDrag[0].dx), 0.0f };
        dxyz *= 0.1f;
        glm::vec4 r = glm::inverse(cubeOrientation) * glm::vec4(cubeRight.x, cubeRight.y, cubeRight.z, 0.0f);
        glm::vec4 u = glm::inverse(cubeOrientation) * glm::vec4(cubeUp.x, cubeUp.y, cubeUp.z, 0.0f);
        glm::vec3 right{ r.x, r.y, r.z };
        glm::vec3 up{ u.x, u.y, u.z };
        cubeOrientation = glm::rotate(cubeOrientation, dxyz.x, right);
        cubeOrientation = glm::rotate(cubeOrientation, dxyz.y, up);
        //NOTE: INVERSING CUBEORIENTATION SEEMED TO WORK??????? IDK WHY BUT SURE

    }
    else if (!newMouse->buttons[0].isHeld)
    {
        clicked = false;
        currentOrientation = cubeOrientation;

    }

    //TODO: THIS ONLY TAKES INTO ACCOUNT THE ORIGINAL ORIENTATION, IT DOES NOT TAKE INTO ACCOUNT
    //WHEN YOU ROTATE THAT NOW THE ORIENTATION IS DIFFERENT SO JUST CHANGING EULER ANGLES DOES NOT 
    //ACTUALLY ROTATE IT CORRECTLY. EG ROTATE 90 ON X AND THEN RELEASING AND THEN ROTATE ON Y SHOULD ROTATE
    //ON AROUND THE NEW ORIENTATION BUT NOW IT ROTATES WEIRDLY AROUND Z INSTEAD (SINCE ROTATED ON X)

    //TODO: DISABLE MOVING CAMERA WHEN ROTATING
}

extern INPUTS g_inputs;
extern MOUSE_INPUTS g_mouse;

void RenderUpdate(double delta)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    UpdateInputs(&g_inputs);
    UpdateMouseButton(&g_mouse);

    LoadShader(g_CubeShader.prog);

    glm::mat4 u_MVP = glm::mat4(1.0f);
    glm::vec3 up{};

    up = glm::normalize(glm::cross(s_camRight, s_camFront));
    s_viewMat = glm::lookAt(s_camPos, s_camPos + s_camFront, up);
    u_MVP = s_projMat * s_viewMat;

    //Set uniforms
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");




    CalculateAndRender(s_projMat, s_viewMat);
    SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    double fps = 1000.0 / delta;
    std::string fpsStr = "fps: " + std::to_string(fps);
    std::string deltaStr = "frame time: " + std::to_string(delta);

    FontRender(fpsStr, 0.0f, 500.0f, 1.0f);
    FontRender(deltaStr, 0.0f, 550.0f, 1.0f);
    FontRender("this is some text", 0.0f, 100.0f, 1.0f);
    //TODO: BUFFER VERTICES ONLY ONCE AND USE A MATRIX TO TRANSFORM THE QUADS TO RENDER
    //TODO: PERHAPS LOOK INTO SIGNED DISTANCE FIELDS

}