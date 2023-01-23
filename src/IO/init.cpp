#include "Updates.h"
#include "GLFW/glfw3.h"
#include "glfwCallbacks.h"
#include "window.h"

WindowData g_windowData{ 1920, 1080, NULL };


void IOInit(void* window)
{
    GLFWwindow* win = (GLFWwindow*)window;
    g_windowData.window = win;
    glfwGetWindowSize(win, &g_windowData.w, &g_windowData.h);
    glfwSetKeyCallback(win, &KeyCallback);
    glfwSetCursorPosCallback(win, &MouseCallback);


    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}