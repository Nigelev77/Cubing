#pragma once

#include "GLFW/glfw3.h"
#include "InputData.h"


extern INPUTS g_inputs;


void KeyCallback(GLFWwindow* window, int key, int action, int scancode, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);
