#version 460 core

in vec3 frag_color;

out vec4 outColor;

uniform float u_colour;
uniform float u_red;

void main(void)
{
    outColor=vec4(u_colour, u_colour, u_colour, 1.0);
}