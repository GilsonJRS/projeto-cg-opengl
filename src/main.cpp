//CPP libs
#include <iostream>
#include <string>
#include <fstream>
#include <stack>

//Our libraries
#include "../include/Shader.h"
#include "../include/Sphere.h"
#include "../include/Electrosphere.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexArray.h"
#include "../include/Camera.h"
#include "../include/Atom.h"
#include "../include/Nucleus.h"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Global Variables
int gWindowWidth  = 800;
int gWindowHeight = 600;
const char* TITLE = {"Atom model"};
GLFWwindow* gWindow = NULL;
std::stack<glm::mat4> mvStack;
GLuint mvLoc, vmLoc, projLoc;
Camera camera((GLfloat)gWindowWidth/(GLfloat)gWindowHeight);
bool update = false;

bool initOpenGL();
void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursorEnterCallBack(GLFWwindow* window, int entered);

int main(void)
{
    if(!initOpenGL())
    {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    Shader shader("shaders/test.vs","shaders/test.fs");
    Atom atom(shader.getProgramId(), 5, 1, glm::vec3(0.0f, 0.0f, 1.0f),glm::vec3(0.0f, 0.0f, 1.0f),glm::vec3(0.0f, 0.0f, 1.0f));
    //Nucleus nucleo(shader.getProgramId(), 1, 20, 20);
    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(gWindow))
    {
        /* Poll for and process events */
        glfwPollEvents();

        /* Render here */
        
        glClear(GL_DEPTH_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT);
          
        
        //camera configs
        mvLoc = glGetUniformLocation(shader.getProgramId(), "mv_matrix");
        vmLoc = glGetUniformLocation(shader.getProgramId(), "vm_matrix");
        projLoc = glGetUniformLocation(shader.getProgramId(), "proj_matrix");
        
        //build camera
        glm::mat4 vmMat = camera.getViewMatrix();
        //perspective matrix
        glm::mat4 projMat = camera.getProjMatrix();
        
        mvStack.push(glm::mat4(1.0f));
        /*mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));//rotation
        mvStack.push(mvStack.top());
        mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));//position
        */
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        shader.bind();
        atom.show(vmMat, projMat, glm::mat4(1.0f));
        
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
    return true;
}

void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode){
    const float cameraSpeed = 0.05f;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(gWindow, GL_TRUE);
    if((key == GLFW_KEY_W && action == GLFW_REPEAT)||
        (key == GLFW_KEY_W && action == GLFW_PRESS))
        camera.updatePos(glm::vec3(0.0f,0.0f, -1.0f));
    if((key == GLFW_KEY_S && action == GLFW_REPEAT)||
        (key == GLFW_KEY_S && action == GLFW_PRESS))
        camera.updatePos(glm::vec3(0.0f,0.0f, +1.0f));
    if((key == GLFW_KEY_A && action == GLFW_REPEAT)||
        (key == GLFW_KEY_A && action == GLFW_PRESS))
        camera.updatePos(glm::vec3(-1.0f,0.0f, 0.0f));
    if((key == GLFW_KEY_D && action == GLFW_REPEAT)||
        (key == GLFW_KEY_D && action == GLFW_PRESS))
        camera.updatePos(glm::vec3(1.0f,0.0f, 0.0f));
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    gWindowHeight = height;
    gWindowWidth = width;
    glViewport(0,0,width, height);
}
