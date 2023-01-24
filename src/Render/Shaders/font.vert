#version 460 core

layout(location=0) in vec4 vert_vertex;

out vec2 frag_texCoords;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(vert_vertex.x, vert_vertex.y, 0.0, 1.0);
    frag_texCoords = vert_vertex.zw;
}