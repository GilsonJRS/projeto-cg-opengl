#include "../include/Texture.h"

Texture::Texture(const char* image){
    glGenTextures(1, &(this->texture_id));
    this->bind();

    int width, height, nrChannels;
    unsigned char *data;

    data = stbi_load(image, &width, &height, &nrChannels, STBI_rgb_alpha);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

    if(data){    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture(){
    glDeleteTextures(1, &(this->texture_id));
}

void Texture::bind(){
    glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Texture::unbind(){
    this->bind();

    int width, height, nrChannels;
    unsigned char *data;

    data = stbi_load("../textures/white1x1.jpeg", &width, &height, &nrChannels, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(data){    
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}