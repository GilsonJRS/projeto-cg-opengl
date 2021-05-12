#include "../include/Sphere.h"

Sphere::Sphere(GLuint program, GLfloat radius,GLfloat verticalResolution, GLfloat horizontalResolution, glm::vec3 color){
    //shader program
    this->shader_id = program;

    //generating sphere
    float x, y, z, xy;
    float lengthInv = 1.0f / radius;

    //sphere color
    this->color = color;

    float sectorStep = 2 * M_PI / horizontalResolution;
    float stackStep = M_PI / verticalResolution;
    float sectorAngle, stackAngle;

    for(int i=0;i<=verticalResolution;++i){
        stackAngle = M_PI / 2 - i * stackStep;

        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);
        
        for(int j=0;j<=horizontalResolution;++j){
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
        
            this->vertices.push_back(x);
            this->vertices.push_back(y);
            this->vertices.push_back(z);

            this->normals.push_back(x * lengthInv);
            this->normals.push_back(y * lengthInv);
            this->normals.push_back(z * lengthInv);
        }
    }

    GLuint k1, k2;
    for(int i=0;i<verticalResolution;++i){
        k1 = i * (horizontalResolution + 1);
        k2 = k1 + horizontalResolution + 1;

        for(int j=0;j<horizontalResolution;++j, ++k1, ++k2){
            if(i != 0){
                this->indices.push_back(k1);
                this->indices.push_back(k2);
                this->indices.push_back(k1+1);
            }
            if(i != (verticalResolution-1)){
                this->indices.push_back(k1+1);
                this->indices.push_back(k2);
                this->indices.push_back(k2+1);
            }
        }
    }
    this->vbo = new VertexBuffer(this->getVertices(), this->getVertexSize());
    this->vbo->bind();
    this->vao = new VertexArray(0,3,0,(const GLvoid*)0);
    this->ibo = new VertexBuffer(this->getIndices(), this->getIndexSize());
}

Sphere::~Sphere(){
}

void Sphere::show(
    glm::mat4 view,
    glm::mat4 projection,
    glm::mat4 model,
    glm::vec3 translate,
    glm::vec3 scale,
    glm::vec3 rotate,
    GLfloat rotate_degree
){
    model = glm::rotate(model, glm::radians(rotate_degree), rotate);
    model = glm::scale(model, scale);
    model = glm::translate(model, translate);
    glUniformMatrix4fv(glGetUniformLocation(this->shader_id, "mv_matrix"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(this->shader_id, "vm_matrix"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(this->shader_id, "proj_matrix"), 1, GL_FALSE, glm::value_ptr(projection));  
    glUniform3fv(glGetUniformLocation(this->shader_id, "color"), 1, glm::value_ptr(this->color));
    //std::cout<<"a"<<std::endl;
    this->vao->bind();
    this->ibo->bindElements();
    glDrawElements(GL_TRIANGLES, this->getIndexSize(), GL_UNSIGNED_INT, NULL);
    this->vao->unbind();
}