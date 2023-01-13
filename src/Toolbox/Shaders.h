#pragma once
#include "GLAD/glad.h"
#include <string_view>
#include "glm.hpp"


struct Shader
{
    GLuint prog, vert, frag;
};

extern Shader g_CubeShader;


/// @brief 
/// @param vPath 
/// @param fPath 
/// @return 
Shader CreateShader(std::string_view vPath, std::string_view fPath);
/// @brief 
/// @param prog 
void LoadShader(GLuint prog);
/// @brief 
/// @param prog 
void UnloadShader(GLuint prog);
/// @brief 
/// @param mat 
/// @param prog 
/// @param name 
void SetUniMat4f(glm::mat4& mat, GLuint prog, std::string_view name);
/// @brief 
/// @param f 
/// @param prog 
/// @param name 
void SetUniFloat(float f, GLuint prog, std::string_view name);
