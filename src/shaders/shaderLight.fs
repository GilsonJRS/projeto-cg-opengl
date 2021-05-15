#version 460 core

in vec3 Normal;
in vec3 vert_color;
in vec3 FragPos;
out vec4 frag_color;
 
uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
    //ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * vec3(1.0f,1.0f,1.0f);
    
    //diffuse
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f,1.0f,1.0f);

    //specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);

    vec3 result = (ambient + diffuse) * vert_color;
    frag_color = vec4(result, 1.0f);
}