#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

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

class VertexArray{
    private:
        GLuint vertex_array_id;
    public:
        VertexArray();
        VertexArray(
            GLuint index,
 	        GLint size,
 	        GLsizei stride,
 	        const GLvoid * pointer);
        ~VertexArray();
        void attribPointer(
            	GLuint index,
                GLint size,
                GLsizei stride,
                const GLvoid * pointer
        );
        void bind();
        void unbind();

};

#endif