/***
 * 
 * Class to create atoms using the class Spheres
 * and Electrosphere
 * 
 * Autors: Gilson & Brendon
 * Date: 13/04/2021
 * 
***/
#ifndef ATOM_H
#define ATOM_H

//CPP libs
#include <vector>
#include <cstdlib>
#include <string>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//Our libraries
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include "../include/Sphere.h"
#include "../include/Electrosphere.h"
#include "../include/Text.h"
#include "../include/Shader.h"

class Atom{
    private:
        unsigned int shader_id;
        std::string initials;
        std::string name;
        std::vector<GLuint> eletronsPerLayer;
        GLuint numElectrons;
        Sphere nucleus;
        GLfloat radius;
        GLfloat atomicMass;
        GLfloat graus2TranslateEletron = 0.f; //
        std::vector<Sphere *> electrons;
        std::vector<Electrosphere *> electrosphere;
        std::vector<glm::mat4> models;
    public:
        Atom(
            GLuint program,
            std::string initials,
            std::string name,
            GLfloat atomicMass,
            GLfloat nucleusRadius,
            GLuint numElectrons,
            std::vector<GLuint> eletronsPerLayer,    
            glm::vec3 nucleusColor,
            glm::vec3 electrosphereColor,
            glm::vec3 electronsColor
        );
        ~Atom();
        //Function to render atom on screen using the show function
        //of the subcomponents
        void show(
            glm::vec3 viewPos,
            glm::vec3 lightPos,
            GLfloat time,
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            Text &textRender,
            Shader &shaderAtom,
            Shader &shaderText,
            glm::vec3 translate = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(1.0f),
            GLfloat rotate_degree = 0.0f 
        );
};

#endif