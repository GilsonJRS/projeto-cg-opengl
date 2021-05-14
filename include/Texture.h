#ifndef TEXTURE_H
#define TEXTURE_H

//CPP libs
#include <iostream>
#include "stb_image.h"
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Texture{
    private:
        GLuint texture_id;
    public:
        Texture(const char* data);
        ~Texture();
        void bind();
        void unbind();
};

#endif