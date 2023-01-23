#include "CubeRender.h"
#include "glad/glad.h"
#include "Toolbox/Shaders.h"
#include "init.h"
#include "gtc/matrix_transform.hpp"

int g_dim = 3;

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
    float dim = (float)g_dim;
    float midDist = dim;

    glm::mat4 cubeScale(1.0f);
    cubeScale = glm::scale(cubeScale, glm::vec3(1.0f / dim, 1.0f / dim, 1.0f / dim));

    glm::mat4 u_MVP{ 1.0f };
    for (int face = 0; face < 6; face++)
    {
        glm::mat4 sTranslate(1.0f);
        glm::mat4 sRotation(1.0f);
        if (face < 4)
        {
            sTranslate = glm::translate(sTranslate, glm::vec3(0.0f, 0.0f, midDist));
            int i = 0;
            for (;i < face && face < 4;i++)
            {
                sRotation = glm::rotate(sRotation, glm::radians(90.0f), Y_AXIS);
            }
            sTranslate = sRotation * sTranslate;

        }
        if (face == 4)
        {
            sTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, midDist));
            sRotation = glm::rotate(sRotation, glm::radians(-90.0f), X_AXIS);
            sTranslate = sRotation * sTranslate;
        }
        if (face == 5)
        {
            sTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, g_dim));
            sRotation = glm::rotate(sRotation, glm::radians(90.0f), X_AXIS);
            sTranslate = sRotation * sTranslate;
        }
        for (int s = 0; s < g_dim * g_dim; s++)
        {

            glm::mat4 fTranslate(1.0f);
            float x = midDist - 1.0f;
            float y = midDist - 1.0f;
            glm::vec3 initPos{ -x, y, 0.0f };
            glm::vec3 translate{ s % g_dim * 2.0f, -(s / g_dim) * 2.0f, 0.0f };
            // fTranslate = glm::scale(fTranslate, scale);
            fTranslate = glm::translate(fTranslate, initPos + translate);
            glm::vec3 scale = glm::vec3(1.0f / dim, 1.0f / dim, 1.0f / dim);
            glm::mat4 u_model = cubeScale * sTranslate * fTranslate;

            // NOTE: I BELIEVE THIS IS CORRECT BUT THE REASON FOR SLOWDOWN IS JUST BECAUSE MORE THIGNS RENDERED
            // AND NOT HAVING FIXED TIME THING

            u_MVP = u_proj * u_view * u_model;


            SetUniMat4f(u_MVP, g_CubeShader.prog, "u_MVP");
            SetUniFloat(((float)face / 6.0f), g_CubeShader.prog, "u_colour");
            SetUniFloat((float)s / (g_dim * g_dim), g_CubeShader.prog, "u_red");
            glDrawElements(GL_TRIANGLES, g_vertexCount, GL_UNSIGNED_INT, NULL);

        }
    }


}

void RotateCube(AXIS axis, DIRECTION dir)
{
    return;
}
