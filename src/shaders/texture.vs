#version 460 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 texCoord;

uniform mat4 mv_matrix;
uniform mat4 vm_matrix;
uniform mat4 proj_matrix;

out vec2 vert_tex;

void main(){
    vert_tex = texCoord;
    gl_Position = proj_matrix * vm_matrix * mv_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}