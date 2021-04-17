//CPP libs
#include <iostream>
#include <string>
#include <fstream>
#include <stack>

#include "../include/Shader.h"
#include "../include/Sphere.h"
#include "../include/VertexBuffer.h"
#include "../include/VertexArray.h"

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
const int gWindowWidth  = 800;
const int gWindowHeight = 600;
const char* TITLE = {"Atom model"};
GLFWwindow* gWindow = NULL;
GLfloat cameraX, cameraY, cameraZ;
std::stack<glm::mat4> mvStack;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
GLuint mvLoc, vmLoc, projLoc;
int height, width;


bool initOpenGL();

void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode);

int main(void)
{
    if(!initOpenGL())
    {
        std::cerr << "Initialization failed" << std::endl;
        return -1;
    }

    Shader shader("shaders/test.vs","shaders/test.fs");
    Sphere bola(5, 36, 18);
   
    VertexBuffer bufferArray(bola.getVertices(), bola.getVertexSize());
    bufferArray.bind();
    VertexArray vs(0,3,0,(const GLvoid*)0);
    VertexBuffer bufferIndex(bola.getIndices(), bola.getIndexSize());
    bufferIndex.bindElements();
   
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;

    glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(gWindow))
    {
        /* Poll for and process events */
        glfwPollEvents();
              
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        shader.bind();  

        //camera configs
        mvLoc = glGetUniformLocation(shader.getProgramId(), "mv_matrix");
        vmLoc = glGetUniformLocation(shader.getProgramId(), "vm_matrix");
        projLoc = glGetUniformLocation(shader.getProgramId(), "proj_matrix");
        
        //build camera
        glm::mat4 mvT = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        glm::mat4 vmMat = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        mvStack.push(mvT);
        //perspective matrix
        glfwGetFramebufferSize(gWindow, &width, &height);
        GLfloat aspect = (GLfloat)gWindowWidth/(GLfloat)gWindowHeight;
        glm::mat4 projMat = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 1000.0f);
        
        mvStack.push(mvStack.top());
        mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));//rotation
        mvStack.push(mvStack.top());
        mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));//position
        
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, value_ptr(mvStack.top()));
        glUniformMatrix4fv(vmLoc, 1, GL_FALSE, value_ptr(vmMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projMat));
        
        vs.bind();
        bufferIndex.bindElements();
        glDrawElements(GL_TRIANGLES, bola.getIndexSize(), GL_UNSIGNED_INT, NULL); 
        vs.unbind();

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

    
    //Initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    
    glfwSetKeyCallback(gWindow, glfw_key);
    return true;
}

void glfw_key(GLFWwindow *window, int key, int scancode, int action, int mode){
    const float cameraSpeed = 0.05f;
    
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(gWindow, GL_TRUE);

     if (key == GLFW_KEY_W && action == GLFW_PRESS)
        cameraPos += cameraSpeed + cameraFront;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        cameraPos -= cameraSpeed + cameraFront;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}