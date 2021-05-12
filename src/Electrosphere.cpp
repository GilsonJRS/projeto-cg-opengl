#include "../include/Electrosphere.h"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include <cmath>

Electrosphere::Electrosphere(GLuint program, GLfloat radiusAtom, GLfloat radiusTube, GLfloat passTorus, GLfloat passTube){
    //shader program
    this->shader_id = program;

    //generating electrosphere
    for(GLfloat grausTorus = 0.f; grausTorus < 360.f; grausTorus += passTorus) {
        GLfloat cosTorus = cos(glm::radians(grausTorus));
        GLfloat sinTorus = sin(glm::radians(grausTorus));
        for(GLfloat grausTube = 0.f; grausTube < 360.f; grausTube += passTube) {
            GLfloat cosTube = cos(glm::radians(grausTube));
            GLfloat sinTube = sin(glm::radians(grausTube));

            this->vertices.push_back((radiusAtom + radiusTube*cosTube)*cosTorus*1.22); //x. 1,22 vezes maior que o raio do Atomo
            this->vertices.push_back((radiusAtom + radiusTube*cosTube)*sinTorus*4.22); //y. 4,22 vezes maior que o raio do Atomo
            this->vertices.push_back(radiusTube*sinTube); //z. Espessura da órbita dos elétrons
        }
    }

    int squaresPerSegment = (int)(360.f/passTube);
    int squareIdx = 0;
    int verticeSize = this->vertices.size()/3;

    //Segmentos do Torus, exceto o que conecta o último segmento ao segmento inicial 
    for(squareIdx; squareIdx < verticeSize - squaresPerSegment; squareIdx++) { //A cada vértice um quadrado
        this->indices.push_back(squareIdx); // triângulo com ângulo reto no primeiro vértice
        this->indices.push_back(squareIdx + squaresPerSegment);  
        if(!((squareIdx + 1) % squaresPerSegment == 0)) { //Enquanto não for a conexão do Tubo
            this->indices.push_back(squareIdx + 1);
            this->indices.push_back(squareIdx + 1);            
            this->indices.push_back(squareIdx + 1 + squaresPerSegment);
        } else { //Último segmento do Tubo: conexão entre o penúltimo com o início do Tubo.
            this->indices.push_back(squareIdx + 1 - squaresPerSegment);
            this->indices.push_back(squareIdx + 1 - squaresPerSegment);
            this->indices.push_back(squareIdx + 1);
        }
        this->indices.push_back(squareIdx + squaresPerSegment);
    }

    //Último segmento do Torus: conexão entre o penúltimo com o início do Torus.
    int toGoFirstTorusSegment = verticeSize - squaresPerSegment;

    for(squareIdx; squareIdx < verticeSize; squareIdx++) {  
        this->indices.push_back(squareIdx); // triângulo com ângulo reto no primeiro vértice
        this->indices.push_back(squareIdx - toGoFirstTorusSegment);
            if(!((squareIdx + 1) % squaresPerSegment == 0)) { //Enquanto não for a conexão do Tubo
                this->indices.push_back(squareIdx + 1);
                this->indices.push_back(squareIdx + 1);
                this->indices.push_back(squareIdx + 1 - toGoFirstTorusSegment);            
            } else { //Último segmento do Tubo: conexão entre o penúltimo com o início do Tubo.
                this->indices.push_back(squareIdx + 1 - squaresPerSegment); //idx.push_back(0);
                this->indices.push_back(squareIdx + 1 - squaresPerSegment); //idx.push_back(0);
                this->indices.push_back(0);
            }
            this->indices.push_back(squareIdx - toGoFirstTorusSegment);
    }

    this->vbo = new VertexBuffer(this->getVertices(), this->getVertexSize());
    this->vbo->bind();
    this->vao = new VertexArray(0,3,0,(const GLvoid*)0);
    this->ibo = new VertexBuffer(this->getIndices(), this->getIndexSize());
}

Electrosphere::~Electrosphere(){

}

void Electrosphere::show(
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
    //std::cout<<"a"<<std::endl;
    this->vao->bind();
    this->ibo->bindElements();
    glDrawElements(GL_TRIANGLES, this->getIndexSize(), GL_UNSIGNED_INT, NULL);
    this->vao->unbind();
}