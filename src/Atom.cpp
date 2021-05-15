#include "../include/Atom.h"

Atom::Atom(
    GLuint program,
    std::string initials,
    std::string name,
    GLfloat nucleusRadius,
    GLuint numElectrons,
    std::vector<GLuint> eletronsPerLayer,    
    glm::vec3 nucleusColor,
    glm::vec3 electrosphereColor,
    glm::vec3 electronsColor
):nucleus{program,nucleusRadius,76,76,nucleusColor}{

    this->numElectrons = numElectrons;
    this->shader_id = program;
    this->radius = nucleusRadius;
    this->initials = initials;
    this->name = name;
    this->eletronsPerLayer = eletronsPerLayer;

    electrons.resize(numElectrons);
    electrosphere.resize(eletronsPerLayer.size());
    models.resize(eletronsPerLayer.size());
    
    for(int i=0; i<eletronsPerLayer.size(); i++){
        electrosphere[i] = new Electrosphere(program, nucleusRadius + 2*i, 0.1, 1, 1);
        if(i%2==0){
            models[i] = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            models[i] = glm::rotate(models[i], glm::radians(180.0f/(eletronsPerLayer.size())*(GLfloat)i), glm::vec3(1.0f, 0.0f, 0.0f));
        }else{
            models[i] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,0.0f));
            models[i] = glm::rotate(models[i], glm::radians(180.0f/(eletronsPerLayer.size())*(GLfloat)i), glm::vec3(1.0f, 0.0f, 0.0f));
        }
    }

    for(int j=0; j<numElectrons; j++){
        electrons[j] = new Sphere(program, 1, 20, 20);        
    }
}
Atom::~Atom(){

}
void Atom::show(
    glm::vec3 viewPos,
    glm::vec3 lightPos,
    GLfloat time,
    glm::mat4 view,
    glm::mat4 projection,
    glm::mat4 model,
    glm::vec3 translate,
    glm::vec3 scale,
    glm::vec3 rotate,
    GLfloat rotate_degree
){
    nucleus.show(viewPos, lightPos,view, projection, model);
    
    this->graus2TranslateEletron = (this->graus2TranslateEletron + 8.f == 360.f) ? 0.f : this->graus2TranslateEletron + 8.f; 

    for(int i=0; i < this->eletronsPerLayer.size(); i++){
        electrosphere[i]->show(viewPos, lightPos, view, projection, models[i]);
        
        GLfloat spaceBetweenEletrons = 360.f/this->eletronsPerLayer[i];
        
        for(int j=0; j < this->eletronsPerLayer[i]; j++){
            GLfloat graus2TranslateEachEletron = this->graus2TranslateEletron + j*spaceBetweenEletrons;
            GLfloat cosTorus = cos(glm::radians(graus2TranslateEachEletron));
            GLfloat sinTorus = sin(glm::radians(graus2TranslateEachEletron));

            electrons[j]->show(viewPos, lightPos, view, projection, 
                                glm::translate(models[i],
                                glm::vec3((this->radius + 2*i)*cosTorus*1.22, //x
                                          (this->radius + 2*i)*sinTorus*4.22, //y
                                          0.f))); //z
        }
    }
}