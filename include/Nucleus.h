#ifndef NUCLEUS_H
#define NUCLEUS_H

//CPP libs
#include <vector>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Our libraries
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/Sphere.h"
#include "../include/Electrosphere.h"

class Nucleus{
    private:
        GLuint protons;
        GLuint neutrons;
        glm::vec3 protonsColor;
        glm::vec3 neutronsColor;
        std::vector<GLfloat> structure;
        std::vector<Sphere *>nucleus;
    public:
        Nucleus(GLuint program,GLfloat radius,  GLuint protons, GLuint neutrons);
        ~Nucleus();
        void show(
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            glm::vec3 translate = glm::vec3(1.0f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(1.0f),
            GLfloat rotate_degree = 0.0f 
        );
};

#endif