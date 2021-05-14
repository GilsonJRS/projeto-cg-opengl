#include "../include/Atom.h"

Atom::Atom(
    GLuint program,
    GLfloat nucleusRadius,
    GLuint numElectrons,
    glm::vec3 nucleusColor,
    glm::vec3 electrosphereColor,
    glm::vec3 electronsColor
):nucleus{program,nucleusRadius,76,76,nucleusColor}{

    this->numElectrons = numElectrons;
    this->shader_id = program;

    electrons.resize(numElectrons);
    electrosphere.resize(numElectrons);
    models.resize(numElectrons);
    
    for(int i=0;i<numElectrons;i++){
        electrons[i] = new Sphere(program, 1, 20, 20);
        electrosphere[i] = new Electrosphere(program, nucleusRadius, 0.1, 1, 1);
        if(i%2==0){
            //models[i] = glm::mat4(1.0f);
            models[i] = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            models[i] = glm::rotate(models[i], glm::radians(180.0f/(numElectrons)*(GLfloat)i), glm::vec3(1.0f, 0.0f, 0.0f));
        }else{
            models[i] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,2.0f,0.0f));
            models[i] = glm::rotate(models[i], glm::radians(180.0f/(numElectrons)*(GLfloat)i), glm::vec3(1.0f, 0.0f, 0.0f));
        }
    }
}
Atom::~Atom(){

}
void Atom::show(
    GLfloat time,
    glm::mat4 view,
    glm::mat4 projection,
    glm::mat4 model,
    glm::vec3 translate,
    glm::vec3 scale,
    glm::vec3 rotate,
    GLfloat rotate_degree
){
    nucleus.show(view, projection, model);
    for(int i=0;i<this->numElectrons;i++){
        electrons[i]->show(view, projection, model);
        electrosphere[i]->show(view, projection, models[i]);
    }
}