#ifndef ATOM_H
#define ATOM_H

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

class Atom{
    private:
        unsigned int shader_id;
        GLuint numElectrons;
        Sphere nucleus;
        std::vector<Sphere *> electrons;
        std::vector<Electrosphere *> electrosphere;
    public:
        Atom(
            GLuint program,
            GLfloat nucleusRadius,
            GLuint numElectrons
        );
        ~Atom();
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