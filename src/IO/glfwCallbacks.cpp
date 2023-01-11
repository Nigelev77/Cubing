#include "glfwCallbacks.h"
#include "InputData.h"

#include "IO_Game_interface.h"

extern INPUTS g_inputs{};

void KeyCallback(GLFWwindow *window, int key, int action, int scancode, int mods)
{
    INPUT_STATE &k = g_inputs.keys[key];
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
    return;
}