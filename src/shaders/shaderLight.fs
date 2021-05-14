#version 460 core

in vec3 Normal;
in vec3 vert_color;
out vec4 frag_color;
 
uniform vec3 lightPos;

void main(){
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0f,1.0f,1.0f);
    
    vec3 result = ambient * vert_color;
    frag_color = vec4(result, 1.0f);
}