#version 460 core

in vec2 frag_texCoords;
out vec4 outColor;


uniform sampler2D u_texture;
uniform vec3 u_textColour;

void main()
{
    vec4 red = vec4(1.0, 1.0, 1.0, texture(u_texture, frag_texCoords).r);
    outColor = vec4(u_textColour, 1.0) * red;
}
