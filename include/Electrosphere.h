/***
 *
 * Class for create Electrospheres
 * 
 * Autors: Gilson & Brendon
 * Date: 13/04/2021 
 *
 ***/
#ifndef ELECTROSPHERE_H
#define ELECTROSPHERE_H

//CPP libs
#include <iostream>
#include <vector>
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

class Electrosphere{
    private:
        unsigned int shader_id;
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
        std::vector<GLfloat> elipseEletrosfera;

        VertexBuffer *vbo, *ibo;
        VertexArray *vao;
    public:
        Electrosphere(GLuint program, GLfloat radiusAtom, GLfloat radiusTube, GLfloat passTorus, GLfloat passTube);
        ~Electrosphere();
        //render electrosphere
        void show(
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            glm::vec3 translate = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(1.0f),
            GLfloat rotate_degree = 0.0f 
        );
        //get vertices data for buffer
        const GLfloat* getVertices(){return this->vertices.data();}
        //get indices data for buffer
        const GLuint* getIndices(){return this->indices.data();} 
        GLuint getVertexSize(){return this->vertices.size() * sizeof(GLfloat);}
        GLuint getIndexSize(){return this->indices.size() * sizeof(GLuint);}
        GLuint getIndexNum(){return this->vertices.size()/3;}
};
#endif