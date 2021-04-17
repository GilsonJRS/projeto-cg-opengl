#version 460 core

layout (location=0) in vec3 pos;

uniform mat4 mv_matrix;
uniform mat4 vm_matrix;
uniform mat4 proj_matrix;

out vec3 vert_color;

void main(){
    vert_color = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = proj_matrix * vm_matrix * mv_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}