#version 460 core

in vec2 vert_tex;

out vec4 frag_color;
uniform sampler2D textureModel;

void main(){
    frag_color = texture(textureModel, vert_tex);
}