#version 460 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;
    
void main(){
    gl_Position = proj_matrix * view_matrix * model_matrix * vec4(vertex.xy, 0.0f, 1.0);
    TexCoords = vertex.zw;
}