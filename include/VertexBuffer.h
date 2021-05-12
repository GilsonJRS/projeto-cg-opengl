/***
 * 
 * Class to handle with buffers
 * 
 * Autors: Gilson & Brendon
 * Date: 13/04/2021
 * 
***/
#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

//CPP libs
#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VertexBuffer{
    private:
        GLuint vertex_buffer_id;
    public:
        VertexBuffer();
        VertexBuffer(const GLfloat* data, GLuint size);
        VertexBuffer(const GLuint* data, GLuint size);
        ~VertexBuffer();
        void bufferData(const GLvoid* data,GLuint size);
        void bind();
        void unbind();
        void bindElements();
        void unbindElements();
};

#endif