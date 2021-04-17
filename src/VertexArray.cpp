#include "../include/VertexArray.h"

VertexArray::VertexArray(){
    glGenVertexArrays(1, &(this->vertex_array_id));
}

VertexArray::VertexArray(
    GLuint index,
 	GLint size,
 	GLsizei stride,
 	const GLvoid * pointer){
    glGenVertexArrays(1, &(this->vertex_array_id));
    this->bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
    this->unbind();
}
VertexArray::~VertexArray(){

}
void VertexArray::attribPointer(	
    GLuint index,
 	GLint size,
 	GLsizei stride,
 	const GLvoid * pointer){ 
    this->bind();
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    this->unbind();
}

void VertexArray::bind(){
    glBindVertexArray(this->vertex_array_id);
}

void VertexArray::unbind(){
    glBindVertexArray(0);
}