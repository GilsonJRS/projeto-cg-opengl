#version 460 core

layout (location=0) in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 vm_matrix;
uniform mat4 proj_matrix;
uniform vec3 color;

out vec3 vert_color;

void main(){
    vert_color = color;
    gl_Position = proj_matrix * vm_matrix * mv_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}