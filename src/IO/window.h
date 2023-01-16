#pragma once
#include "GLFW/glfw3.h"

struct WindowData
{
    int w, h;
    GLFWwindow* window;
};

extern WindowData g_windowData;