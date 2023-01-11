#include <iostream>
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

int main(int, char **)
{

    if (!glfwInit())
        return -1;

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "Cubing", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD init failed"
                  << "\n";
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
