#version 460 core

layout (location=0) in vec3 pos;
layout (location=1) in vec3 aNormal;

uniform mat4 mv_matrix;
uniform mat4 vm_matrix;
uniform mat4 proj_matrix;
uniform vec3 color;

out vec3 vert_color;
out vec3 Normal;
out vec3 FragPos;

void main(){
    Normal = mat3(transpose(inverse(mv_matrix)))*aNormal;
    vert_color = color;
    FragPos = vec3(mv_matrix * vec4(pos, 1.0));
    gl_Position = proj_matrix * vm_matrix * mv_matrix * vec4(pos.x, pos.y, pos.z, 1.0);
}