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
