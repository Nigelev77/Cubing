#include "FontInit.h"
#include "FontRender.h"
#include "Toolbox/Shaders.h"
#include "glm/gtc/matrix_transform.hpp"
static glm::mat4 u_proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);


void FontRender(std::string_view str, float x, float y, float scale)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    LoadShader(g_fontShader.prog);
    glUniform3f(glGetUniformLocation(g_fontShader.prog, "u_textColour"), 0.0f, 1.0f, 1.0f);
    SetUniMat4f(u_proj, g_fontShader.prog, "u_MVP");
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(g_fontao);

    for (const auto& c : str)
    {
        Char ch = g_charMap[c];
        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;
        float w = ch.size.x * scale;
        float h = ch.size.y * scale;


        float vertices[6][4] =
        {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
        };
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, g_fontbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.adv >> 6) * scale;
    }

    //NOTE:THINK ABOUT WHY DISABLING DEPTH TEST AND RENDERING TEXT FIRST RENDERS IT BEHIND EVERYTHING
    //NOTE: LOOK UP WHY TEXT RENDERING SHOULD BE DONE LAST
    //NOTE: THINK ABOUT WHY EVEN IF CLEARING DEPTH BUFFER, IF RENDERED FIRST THERE IS NO TRANSPARENCY/GREY STILL APPEARS
    //NOTE: LOOK UP DEPTH TESTING AND THE DEPTH BUFFER AGAIN WHICH MAY HELP
}





