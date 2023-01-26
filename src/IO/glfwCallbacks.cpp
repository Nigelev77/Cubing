#include "glad/glad.h"
#include "glfwCallbacks.h"
#include "InputData.h"
#include "window.h"
#include "IO_Game_interface.h"

INPUTS g_inputs{};
MOUSE_INPUTS g_mouse{};

#include <iostream>

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, true);
    }
    INPUT_STATE& k = g_inputs.keys[key];
    switch (action)
    {
    case GLFW_REPEAT:
    case GLFW_PRESS:
    {
        if (k.isPressed)
            k.isHeld = true;
        k.isPressed = true;
        break;
    }
    case GLFW_RELEASE:
    {
        k.isHeld = false;
        k.isPressed = false;
        break;
    }
    }
    UpdateInputs(&g_inputs);
    //NOTE: WHEN THIS IS IMPLEMENTED UNCOMMENT THIS
    return;
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    g_windowData.w = width;
    g_windowData.h = height;
    glViewport(0, 0, g_windowData.w, g_windowData.h);
}

void MouseCallback(GLFWwindow* window, double x, double y)
{
    double lX = g_mouse.x, lY = g_mouse.y;

    g_mouse.dx = (x - lX) * 0.01f;
    g_mouse.dy = (y - lY) * 0.01f;
    g_mouse.x = x;
    g_mouse.y = y;
    UpdateMouse(&g_mouse);
    return;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    INPUT_STATE& b = g_mouse.buttons[button];
    switch (action)
    {
    case GLFW_PRESS:
    {
        b.isHeld = true;
        b.isPressed = true;
        break;
    }
    case GLFW_RELEASE:
    {
        b.isHeld = false;
        b.isPressed = false;
        break;
    }
    }
    UpdateMouseButton(&g_mouse);
    return;
}
