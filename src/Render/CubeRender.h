#pragma once
#include "glm.hpp"



extern int g_dim;

enum AXIS
{
    X, Y, Z
};

enum DIRECTION
{
    CW, ACW
};

void ChangeDimensionality(int n);
void CalculateAndRender(glm::mat4& u_proj, glm::mat4& u_view);
void RotateCube(AXIS axis, DIRECTION dir);