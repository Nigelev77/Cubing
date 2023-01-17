#include "CubeRender.h"
#include "glad/glad.h"
#include "Toolbox/Shaders.h"
#include "init.h"
#include "gtc/matrix_transform.hpp"

int g_dim = 1;

void ChangeDimensionality(int n)
{
    g_dim = n;
}

#include <vector>
static std::vector<std::vector<char>> s_colours{};
static glm::vec3 s_orientation{ 0.0f, 0.0f, 0.0f };
const static glm::vec3 X_AXIS{ 1.0f, 0.0f, 0.0f };
const static glm::vec3 Y_AXIS{ 0.0f, 1.0f, 0.0f };
const static glm::vec3 Z_AXIS{ 0.0f, 0.0f, 1.0f };
const static glm::vec3 ZERO_VEC{ 0.0f, 0.0f, 0.0f };


void CalculateAndRender(glm::mat4& u_proj, glm::mat4& u_view)
{
    glm::mat4 cubeRotation{ 1.0f };
    // cubeRotation = glm::rotate(cubeRotation, glm::radians(s_orientation.x), X_AXIS);
    // cubeRotation = glm::rotate(cubeRotation, glm::radians(s_orientation.y), Y_AXIS);
    // cubeRotation = glm::rotate(cubeRotation, glm::radians(s_orientation.z), Z_AXIS);

    LoadShader(g_CubeShader.prog);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 u_MVP{ 1.0f };
    for (int face = 0; face < 6; face++)
    {
        glm::mat4 sTranslate{ 1.0f };
        if (face < 4)
        {

            sTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * sTranslate;
            int i = 0;
            for (;i < face && face < 4;i++)
            {
                sTranslate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), Y_AXIS) * sTranslate;
            }
            // sTranslate = glm::translate(glm::mat4(1.0f), -glm::vec3(0.0f, 0.0f, 1.0f)) * sTranslate;
        }
        //sTranslate *= glm::translate(glm::mat4(1.0f), -glm::vec3(0.0f, 0.0f, 1.0f));
        if (face == 4)
        {
            sTranslate = glm::mat4(1.0f);
            sTranslate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), X_AXIS) * sTranslate;
            sTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * sTranslate;
            //sTranslate = glm::translate(sTranslate, -glm::vec3(0.0f, 2.0f, 0.0f));
        }
        if (face == 5)
        {
            sTranslate = glm::mat4{ 1.0f };
            sTranslate = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), X_AXIS) * sTranslate;
            sTranslate = glm::translate(glm::mat4(1.0f), -glm::vec3(0.0f, 1.0f, 0.0f)) * sTranslate;
            //sTranslate = glm::translate(sTranslate, glm::vec3(0.0f, -1.0f, 0.0f));
        }
        for (int s = 0; s < g_dim; s++)
        {

            u_MVP = u_proj * u_view * sTranslate;
            SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");
            SetUniFloat(((float)face / 6.0f), g_CubeShader.prog, "u_colour");
            glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, NULL);
        }
    }


}

void RotateCube(AXIS axis, DIRECTION dir)
{
    return;
}
