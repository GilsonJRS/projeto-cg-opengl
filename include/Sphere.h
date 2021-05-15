/***
 * 
 * Class to create spheres
 * 
 * Autors: Gilson & Brendon
 * Date: 13/04/2021
 * 
***/
#ifndef SPHERE_H
#define SPHERE_H

//CPP libs
#include <iostream>
#include <vector>
#include <cmath>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//includes
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"

class Sphere{
    private:
        unsigned int shader_id;
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        VertexBuffer *vbo, *ibo;
        VertexArray *vao;
        glm::vec3 color;
    public:
        Sphere(
            GLuint program, 
            GLfloat radius, 
            GLfloat verticalResolution, 
            GLfloat horizontalResolution, 
            glm::vec3 color=glm::vec3(1.0f,1.0f,1.0f)
        );
        ~Sphere();
        void show(
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            glm::vec3 translate = glm::vec3(0.0f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(1.0f),
            GLfloat rotate_degree = 0.0f 
        );
        //get vertices data for buffer
        const GLfloat* getVertices(){return this->vertices.data();}
        //get indices data for buffer
        const GLuint* getIndices(){return this->indices.data();} 
        std::vector<GLfloat> getVertexArray(){return this->vertices;};
        GLuint getVertexSize(){return this->vertices.size() * sizeof(GLfloat);}
        GLuint getIndexSize(){return this->indices.size() * sizeof(GLuint);}
        GLuint getIndexNum(){return this->vertices.size()/3;}
};
#endif