#pragma once
#include "GLFW/glfw3.h"

enum INPUT_STATE
{
    INPUT_PRESSED,
    INPUT_HELD,
    INPUT_RELEASED
};

struct INPUTS
{
    INPUT_STATE c[GLFW_KEY_LAST];
};
