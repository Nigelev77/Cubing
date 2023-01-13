#include "Shaders.h"
#include <fstream>
#include <sstream>
#include "ubiq.h"
#include <iostream>

Shader g_CubeShader{};


GLint CompileShader(GLuint shader)
{
    glCompileShader(shader);
    GLint stat;
    if (glGetShaderiv(shader, GL_COMPILE_STATUS, &stat); !stat)
    {
        char infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        std::cout << infoLog << "\n";
    }
    return stat;
}


Shader CreateShader(std::string_view vPath, std::string_view fPath)
{
    GLuint prog, vert, frag;


    prog = glCreateProgram();
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);


    std::cout << "Creating shader with rel path of" << vPath << "\n";
    { //Vertex
        std::ifstream file{ vPath.data(), std::ios::in };
        std::stringstream ss;
        ss << file.rdbuf();
        const std::string src = ss.str();
        std::cout << "Content of vert is " << src << "\n";
        const char* c_src = src.c_str();
        glShaderSource(vert, 1, &c_src, NULL);
        int stat = CompileShader(vert);
        if (!stat) return { UINT32_MAX, UINT32_MAX, UINT32_MAX };
        file.close();
    }

    std::cout << "Creating shader with rel path of" << fPath << "\n";
    {
        std::ifstream file{ fPath.data(), std::ios::in };
        std::stringstream ss;
        ss << file.rdbuf();
        const std::string src = ss.str();
        std::cout << "Contents of frag is " << src << "\n";
        const char* c_src = src.c_str();
        glShaderSource(frag, 1, &c_src, NULL);
        int stat = CompileShader(frag);
        if (!stat) return { UINT32_MAX, UINT32_MAX, UINT32_MAX };
        file.close();
    }
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);

    std::cout << "Created program with ID " << prog << "\n";
    return { prog, vert, frag };

}

void LoadShader(GLuint prog)
{
    glUseProgram(prog);
}

void UnloadShader(GLuint prog)
{
    glUseProgram(0);
}

void SetUniMat4f(glm::mat4& mat, GLuint prog, std::string_view name)
{
    glUseProgram(prog);
    GLuint loc = glGetUniformLocation(prog, name.data());
    glUniformMatrix4fv(loc, 1, false, &mat[0][0]);
}

void SetUniFloat(float f, GLuint prog, std::string_view name)
{
    glUseProgram(prog);
    GLuint loc = glGetUniformLocation(prog, name.data());
    glUniform1f(loc, f);
}

