#include "FontInit.h"
#include "init.h"


#include <iostream>
#include "glad/glad.h"

FT_Face g_font;
std::unordered_map<char, Char> g_charMap;

GLuint g_fontao;
GLuint g_fontbo;
int g_fontVertex;

void FontInit()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "FREETYPE COULD NOT BE INIT\n";
        return;
    }

    if (FT_New_Face(ft, "../res/fonts/arial.ttf", 0, &g_font))
    {
        std::cout << "COULD NOT LOAD FONT\n";
        return;
    }

    FT_Set_Pixel_Sizes(g_font, 0, 48);

    if (FT_Load_Char(g_font, 'X', FT_LOAD_RENDER))
    {
        std::cout << "COULD NOT LOAD GLYPH\n";
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128;c++)
    {
        if (FT_Load_Char(g_font, c, FT_LOAD_RENDER))
        {
            std::cout << "Failed to load Glyph\n";
            continue;
        }
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, g_font->glyph->bitmap.width,
            g_font->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g_font->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        g_charMap.emplace(std::pair<char, Char>(c, Char{
            texID,
            glm::ivec2(g_font->glyph->bitmap.width, g_font->glyph->bitmap.rows),
            glm::ivec2(g_font->glyph->bitmap_left, g_font->glyph->bitmap_top),
            (unsigned int)g_font->glyph->advance.x
            }));
    }

    //NOTE: PROBABLY NEED TO CLEAN UP g_font by using FT_DONE_FACE() and FT_DONE_FREETYPE()
    glGenVertexArrays(1, &g_fontao);
    glGenBuffers(1, &g_fontbo);
    glBindVertexArray(g_fontao);
    glBindBuffer(GL_ARRAY_BUFFER, g_fontbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}