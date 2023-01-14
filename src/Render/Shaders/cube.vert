#version 460 core

layout(location=0)in vec3 vert_pos;

out vec3 frag_color;

uniform mat4 u_MVP;

void main(void)
{
    gl_Position=u_MVP * vec4(vert_pos,1.0);
    frag_color = vec3(1.0, 0.0, 0.0);
}
