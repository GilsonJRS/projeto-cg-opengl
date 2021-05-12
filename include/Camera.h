/***
 * 
 * Class to create and control the camera(view) and
 * projection matrix
 * 
 * Autors: Gilson & Brendon
 * Date: 13/04/2021
 * 
***/
#ifndef CAMERA_H
#define CAMERA_H

//CPP libs
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    private:
        glm::mat4 viewMatrix;
        glm::mat4 projMatrix;
        glm::vec3 cameraPosition;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        GLfloat horizontalAngle;
        GLfloat verticalAngle;
        GLfloat FOV;
        GLfloat near;
        GLfloat far;
        GLfloat viewportAspectRatio;
    public:
        Camera(GLfloat aspect);
        ~Camera();
        //camera position
        void setPos(glm::vec3 pos);
        void updatePos(glm::vec3 pos);
        //camera FOV
        void setFOV(GLfloat FOV);
        //change planes of frustum
        void setNearPlane();
        void setFarPlane();
        //camera orientation
        void setOrientation(GLfloat horizontal, GLfloat vertical);
        void updateOrientation(GLfloat horizontal, GLfloat vertical);
        //camera look at
        void setLookAt(glm::vec3 look);
        void updateLookAt();
        //normalize angles
        void normalizeAngles();
        //gets
        glm::mat4 getViewMatrix();
        glm::mat4 getProjMatrix();
        glm::mat4 getOrientation();

};
#endif