#version 460 core

layout(location=0)in vec3 vert_pos;

out vec3 frag_color;


void main(void)
{
    gl_Position=vec4(vert_pos,1.0);
    frag_color = vert_pos;
}
