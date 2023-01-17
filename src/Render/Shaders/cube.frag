#version 460 core

in vec3 frag_color;

out vec4 outColor;

uniform float u_colour;

void main(void)
{
    outColor=vec4(u_colour, u_colour, u_colour, 0.5);
}