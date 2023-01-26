#pragma once
#include "GLFW/glfw3.h"

struct INPUT_STATE
{
    bool isPressed;
    bool isHeld;
};

struct INPUTS
{
    INPUT_STATE keys[GLFW_KEY_LAST];
};

struct MOUSE_INPUTS
{
    double x, y;
    double dx, dy;

    INPUT_STATE buttons[GLFW_MOUSE_BUTTON_LAST];
};