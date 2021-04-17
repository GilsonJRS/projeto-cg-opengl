/***
 * 
 * Class to handle with shaders
 * Autors: Gilson & Brendon
 * Date: 13/04/2021
 * 
***/
#ifndef SHADER_H
#define SHADER_H

//CPP libs
#include <iostream>
#include <fstream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    private:
        GLuint program_id;
    public:
        Shader(const char* vs, const char* fs);
        ~Shader();
        void bind();
        void unbind();
        GLuint getProgramId();
};

#endif