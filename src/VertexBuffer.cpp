#include "../include/VertexBuffer.h"

VertexBuffer::VertexBuffer(){
    glGenBuffers(1, &(this->vertex_buffer_id));
}

VertexBuffer::VertexBuffer(const GLfloat* data, GLuint size){
    glGenBuffers(1, &(this->vertex_buffer_id));
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::VertexBuffer(const GLuint* data, GLuint size){
    glGenBuffers(1, &(this->vertex_buffer_id));
    this->bindElements();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer(){
    glDeleteVertexArrays(1, &(this->vertex_buffer_id));
}

void VertexBuffer::bind(){
    glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_id);
}

void VertexBuffer::bindElements(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vertex_buffer_id);
}

void VertexBuffer::bufferData(const GLvoid* data,GLuint size){
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}