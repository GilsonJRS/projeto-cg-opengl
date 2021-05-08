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

class Electrosphere{
    private:
        unsigned int shader_id;
        std::vector<GLuint> indices;
        std::vector<GLfloat> vertices;
        std::vector<GLfloat> normals;
    public:
        Electrosphere(GLfloat radiusAtom, GLfloat radiusTube, GLfloat passTorus, GLfloat passTube);
        ~Electrosphere();
        void show(
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