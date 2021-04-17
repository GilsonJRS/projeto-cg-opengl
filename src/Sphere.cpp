#include "../include/Sphere.h"
#include "../include/VertexArray.h"
#include "../include/VertexBuffer.h"
#include <cmath>

Sphere::Sphere(GLfloat radius,GLfloat verticalResolution, GLfloat horizontalResolution){
    float x, y, z, xy;
    float lengthInv = 1.0f / radius;

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
}

Sphere::~Sphere(){

}
/*void Sphere::show(
    glm::vec3 translate = glm::vec3(1.0f),
    glm::vec3 scale = glm::vec3(1.0f),
    glm::vec3 rotate = glm::vec3(1.0f),
    GLfloat rotate_degree = 0.0f
){

}*/