#include "../include/Electrosphere.h"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include <cmath>

Electrosphere::Electrosphere(GLfloat radiusAtom, GLfloat radiusTube, GLfloat passTorus, GLfloat passTube){
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
}

Electrosphere::~Electrosphere(){

}