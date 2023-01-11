#include <iostream>
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "Updates.h"
#include <chrono>

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

    auto last = std::chrono::steady_clock::now();

    { // All Inits
      // RenderInit(); not implemented yet
    }

    while (!glfwWindowShouldClose(window))
    {
        auto time = std::chrono::steady_clock::now();

        double delta = (time - last).count();
        // RenderUpdate(delta); not implemented yet
        glfwPollEvents();
        glfwSwapBuffers(window);

        last = time;
    }
}
