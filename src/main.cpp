//CPP libs
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <sstream>
#include <tuple>

//Our libraries
#include "../include/Shader.h"
#include "../include/Sphere.h"
#include "../include/Electrosphere.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/Camera.h"
#include "../include/Atom.h"
#include "../include/Nucleus.h"
#include "../include/Texture.h"
#include "../include/Text.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//freetype
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

//Global Variables
int gWindowWidth  = 800;
int gWindowHeight = 600;
const char* TITLE = {"Atom model"};
GLFWwindow* gWindow = NULL;
std::stack<glm::mat4> mvStack;
GLuint mvLoc, vmLoc, projLoc, principalShader;
Camera camera((GLfloat)gWindowWidth/(GLfloat)gWindowHeight);
bool update = false;
int actual=0;

Atom *atom;
std::vector<Atom *> atoms;
std::vector<std::tuple<std::string, std::string, GLfloat, GLuint, std::vector<GLuint>>> data;

bool initOpenGL();
void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursorEnterCallBack(GLFWwindow* window, int entered);

void drawBackground(Texture &textura, GLfloat height, GLfloat width){
    std::vector <GLfloat> verticesBG = {
        -width, height, 0.f,        0.f, 1.f,
         width, height, 0.f,        1.f, 1.f,
         width, -height, 0.f,       1.f, 0.f,
        -width, -height, 0.f,       0.f, 0.f,
    };

    std::vector<GLuint> indicesBG = {0, 1, 2, 2, 0, 3};
    
    VertexBuffer *vbo = new VertexBuffer(verticesBG.data(), verticesBG.size()*sizeof(GLfloat));
    VertexArray *vao = new VertexArray();
    vao->attribPointer(0, 3, sizeof(GLfloat)*5, (const GLvoid*)0);
    vao->attribPointer(1, 2, sizeof(GLfloat)*5, (const GLvoid*)(sizeof(GLfloat)*3));
    VertexBuffer *ibo = new VertexBuffer(indicesBG.data(), indicesBG.size()*sizeof(GLuint));
    vao->bind();
    vbo->bind();
    ibo->bindElements();
    textura.bind();

    glDrawElements(GL_TRIANGLES, indicesBG.size(), GL_UNSIGNED_INT, NULL);

    vao->unbind();
}


int main(void)
{
    if(!initOpenGL())
    {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    //objects shader
    Shader shader("src/shaders/shaderLight.vs","src/shaders/shaderLight.fs");
    principalShader = shader.getProgramId();
    //shader for texture of background
    Shader shaderTexture("src/shaders/texture.vs","src/shaders/texture.fs");
    //shader for text
    Shader shaderText("src/shaders/shaderText.vs", "src/shaders/shaderText.fs");
    Texture fundo("textures/andromedaWallpaper.jpg");
    Text text(std::string("resources/Arial.ttf"));
    
    std::ifstream file("resources/atomsDB.csv");
    std::string line, word, initial, name, weight, numElectron;
    int controller = 0;
    while(std::getline(file,line)){
        std::vector<GLuint> electronsPerLayer;
        controller = 0;
        std::stringstream parser(line);
        while(std::getline(parser, word, ',')){
            switch (controller){
                case 0:
                    initial = word;
                    break;
                case 1:
                    name = word;
                    break;
                case 2:
                    weight = word;
                    break;
                case 3:
                    numElectron = word;
                    break;
                default:
                    electronsPerLayer.push_back(std::stoi(word));
                    break;
            }
            controller++;
        }
        data.push_back(std::make_tuple(initial, name, std::stof(weight), std::stoi(numElectron), electronsPerLayer));
    }
    file.close();
    atoms.resize(118, NULL);
    atoms[0] = 
    new Atom(
        shader.getProgramId(),
        std::get<0>(data[actual]),
        std::get<1>(data[actual]),
        std::get<2>(data[actual]),
        //NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin
        ( ( ( std::get<2>(data[actual]) - std::get<2>(data[0]) ) * (15.0f - 5.0f) ) / ( std::get<2>(data[117]) - std::get<2>(data[0]) ) ) + 5.0f,
        std::get<3>(data[actual]),
        std::get<4>(data[actual]),
        glm::vec3(0.0f,0.0f,1.0f),
        glm::vec3(1.0f,1.0f,1.0f),
        glm::vec3(1.0f,0.0f,0.0f)
    );
    atom = atoms[actual];

    while (!glfwWindowShouldClose(gWindow))
    {
        glfwPollEvents();
        
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        

        //build camera
        glm::mat4 vmMat = camera.getViewMatrix();
        //perspective matrix
        glm::mat4 projMat = camera.getProjMatrix();

        //Se usa uma das duas, sem conjugar, funciona normal o background
        glm:: mat4 model = glm::rotate(glm::mat4(1.f), glm::radians(-camera.getAngles()[0]), glm::vec3(0.f, 1.f, 0.f)); 
        model = glm::rotate(model, glm::radians(-camera.getAngles()[1]), glm::vec3(1.f, 0.f, 0.f));
        model = glm::translate(model, glm::vec3(camera.getPos()[0], camera.getPos()[1], -450.f));

        shaderTexture.bind();
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramId(), "mv_matrix"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramId(), "vm_matrix"), 1, GL_FALSE, glm::value_ptr(vmMat));
        glUniformMatrix4fv(glGetUniformLocation(shaderTexture.getProgramId(), "proj_matrix"), 1, GL_FALSE, glm::value_ptr(projMat));  
        drawBackground(fundo, 400.f, 711.45f); //711 e 400 Textura escalonada proporcionalmente
        
        atom->show(camera.getPos(), glm::vec3(0.0f,50.0f,0.0f),0, vmMat, projMat, glm::mat4(1.0f), text, shader, shaderText);
        
        float mouse = 0.1f;
        double mouseX, mouseY;
        glfwGetCursorPos(gWindow, &mouseY, &mouseX);
        mouseX-=50.0f;mouseY-=50.0f;
        camera.updateOrientation(mouse*(GLfloat)mouseX, mouse*(GLfloat)mouseY);
        glfwSetCursorPos(gWindow,50,50);

        glfwSwapBuffers(gWindow);
    }
    glfwTerminate();
    return 0;
}

bool initOpenGL()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "GLFW initialization failed" << std::endl;
        return false;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 10);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //only to support MAC
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, TITLE, NULL, NULL);
    if (gWindow == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(gWindow);
    glfwSetFramebufferSizeCallback(gWindow, framebuffer_size_callback);
    
    //Initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    
    glfwSetKeyCallback(gWindow, glfw_key);
    glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    //glfwSetInputMode(gWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    //glfwSetMouseButtonCallback(gWindow, mouse_button_callback);
    //glfwSetCursorEnterCallback(gWindow, cursorEnterCallBack);
    glEnable(GL_MULTISAMPLE);

    return true;
}

void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode){
    const float cameraSpeed = 0.05f;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(gWindow, GL_TRUE);
    if(((key == GLFW_KEY_W && action == GLFW_REPEAT)||
        (key == GLFW_KEY_W && action == GLFW_PRESS))&&
        camera.getPos()[2] > 4.f)
        camera.updatePos(glm::vec3(0.0f,0.0f, -1.0f));

    if(((key == GLFW_KEY_S && action == GLFW_REPEAT)||
        (key == GLFW_KEY_S && action == GLFW_PRESS))&&
        (camera.getPos()[2] < 243.f))
        camera.updatePos(glm::vec3(0.0f,0.0f, +1.0f));

    if(((key == GLFW_KEY_A && action == GLFW_REPEAT)||
        (key == GLFW_KEY_A && action == GLFW_PRESS)))
        camera.updatePos(glm::vec3(-1.0f,0.0f, 0.0f));
    
    if(((key == GLFW_KEY_D && action == GLFW_REPEAT)||
        (key == GLFW_KEY_D && action == GLFW_PRESS)))
        camera.updatePos(glm::vec3(1.0f,0.0f, 0.0f));   

    
    if(((key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)||
        (key == GLFW_KEY_RIGHT && action == GLFW_PRESS))){
        if(actual < 117)
            actual++;
        if(atoms[actual]==NULL){
            atoms[actual] = 
                new Atom(
                    principalShader,
                    std::get<0>(data[actual]),
                    std::get<1>(data[actual]),
                    std::get<2>(data[actual]),
                    ( ( ( std::get<2>(data[actual]) - std::get<2>(data[0]) ) * (15.0f - 5.0f) ) / ( std::get<2>(data[117]) - std::get<2>(data[0]) ) ) + 5.0f,
                    std::get<3>(data[actual]),
                    std::get<4>(data[actual]),
                    glm::vec3(0.0f,0.0f,1.0f),
                    glm::vec3(1.0f,1.0f,1.0f),
                    glm::vec3(1.0f,0.0f,0.0f)
                );
        }
        atom=atoms[actual];
    }
        
    if(((key == GLFW_KEY_LEFT && action == GLFW_REPEAT)||
        (key == GLFW_KEY_LEFT && action == GLFW_PRESS))){
        if(actual > 0)
            actual--; 
        atom=atoms[actual];
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    gWindowHeight = height;
    gWindowWidth = width;
    glViewport(0,0,width, height);
}
