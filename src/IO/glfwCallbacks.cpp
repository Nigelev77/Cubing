#include "glad/glad.h"
#include "glfwCallbacks.h"
#include "InputData.h"
#include "window.h"
#include "IO_Game_interface.h"

INPUTS g_inputs{};

void KeyCallback(GLFWwindow* window, int key, int action, int scancode, int mods)
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
    //UpdateInputs(&g_inputs); NOTE: WHEN THIS IS IMPLEMENTED UNCOMMENT THIS
    return;
}

void WindowResizeCallback(GLFWwindow* window, int width, int height)
{
    g_windowData.w = width;
    g_windowData.h = height;
    glViewport(0, 0, g_windowData.w, g_windowData.h);
}