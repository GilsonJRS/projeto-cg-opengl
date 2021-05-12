#include "../include/Nucleus.h"

Nucleus::Nucleus(GLuint program,GLfloat radius,  GLuint protons, GLuint neutrons){
    Sphere tempSphere(program, radius, protons, neutrons );
    this->structure = tempSphere.getVertexArray();
    //tempSphere.~Sphere();

    for(int i=0;i<(protons+neutrons);i++){
        if(i%2==0)
            this->nucleus.push_back(new Sphere(program, 1, 20, 20,glm::vec3(1.0f,0.0f,0.0f)));
        else
            this->nucleus.push_back(new Sphere(program, 1, 20, 20,glm::vec3(0.0f,0.0f,1.0f)));
    }
}

Nucleus::~Nucleus(){};

void Nucleus::show(
    glm::mat4 view,
    glm::mat4 projection,
    glm::mat4 model,
    glm::vec3 translate,
    glm::vec3 scale,
    glm::vec3 rotate,
    GLfloat rotate_degree
){
    int j=0;
    //std::cout<<structure.size();
    for(int i=0;i<nucleus.size();i++){
        nucleus[i]->show(view, projection, model, glm::vec3(structure[j]+1.0f,structure[j+1]+1.0f,structure[j+2]+1.0f));
        j+=9;
    }
}