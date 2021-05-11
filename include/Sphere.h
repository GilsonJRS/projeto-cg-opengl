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
    public:
        Sphere(GLuint program, GLfloat radius, GLfloat verticalResolution, GLfloat horizontalResolution);
        ~Sphere();
        void show(
            glm::mat4 view,
            glm::mat4 projection,
            glm::mat4 model,
            glm::vec3 translate = glm::vec3(1.0f),
            glm::vec3 scale = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(1.0f),
            GLfloat rotate_degree = 0.0f 
        );
        const GLfloat* getVertices(){return this->vertices.data();}
        const GLuint* getIndices(){return this->indices.data();} 
        GLuint getVertexSize(){return this->vertices.size() * sizeof(GLfloat);}
        GLuint getIndexSize(){return this->indices.size() * sizeof(GLuint);}
        GLuint getIndexNum(){return this->vertices.size()/3;}
};
#endif