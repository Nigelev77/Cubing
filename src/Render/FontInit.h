#pragma once
#include "init.h"
#include <ft2build.h>
#include FT_FREETYPE_H



#include "glm/glm.hpp"
struct Char
{
    unsigned int TextureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int adv;
};
extern FT_Face g_font;

#include <unordered_map>
extern std::unordered_map<char, Char> g_charMap;

void FontInit();

