#include "../include/Atom.h"

Atom::Atom(
    GLuint program,
    GLfloat nucleusRadius,
    GLuint numElectrons,
    glm::vec3 nucleusColor,
    glm::vec3 electrosphereColor,
    glm::vec3 electronsColor
):nucleus{program,nucleusRadius,76,58,nucleusColor}{
    this->numElectrons = numElectrons;
    this->shader_id = program;
    electrons.resize(numElectrons);
    electrosphere.resize(numElectrons);
    for(int i=0;i<numElectrons;i++){
        electrons[i] = new Sphere(program, 1, 20, 20);
        electrosphere[i] = new Electrosphere(program, 5, 0.1, 1, 1);
    }
}
Atom::~Atom(){

}
void Atom::show(
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
        electrosphere[i]->show(view, projection, model);
    }
}