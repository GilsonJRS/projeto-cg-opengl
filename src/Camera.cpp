#include "../include/Camera.h"

Camera::Camera(GLfloat aspect){
    this->viewportAspectRatio = aspect;
    this->cameraPosition = glm::vec3(0.0f, 10.0f,  110.0f);
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
    this->FOV = 60.0f;
    this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + cameraFront, cameraUp);
    this->projMatrix = glm::perspective(glm::radians(this->FOV), viewportAspectRatio, 0.1f, 1000.0f);
    this->horizontalAngle = 0.0f;
    this->verticalAngle = 0.0f;
}
Camera::~Camera(){}
glm::mat4 Camera::getViewMatrix(){
    return this->viewMatrix * this->getOrientation();
}
glm::mat4 Camera::getProjMatrix(){
    return this->projMatrix;
}
void Camera::updatePos(glm::vec3 pos){
    this->cameraPosition+=pos;
    this->updateLookAt();
}
void Camera::updateLookAt(){
    this->viewMatrix = glm::lookAt(this->cameraPosition, this->cameraPosition + cameraFront, cameraUp);
}
glm::mat4 Camera::getOrientation(){
    glm::mat4 orientation(1.0f);
    orientation = glm::rotate(orientation, glm::radians(verticalAngle), glm::vec3(1.0f, 0.0f, 0.0f));
    orientation = glm::rotate(orientation, glm::radians(horizontalAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    return orientation;
}
void Camera::updateOrientation(GLfloat vertical, GLfloat horizontal){
    this->horizontalAngle += horizontal;
    this->verticalAngle += vertical;
    normalizeAngles();
}
void Camera::normalizeAngles(){
    this->horizontalAngle = fmodf(this->horizontalAngle, 360.0f);

    if(this->horizontalAngle < 0.0f)
        this->horizontalAngle += 360.0f;
    if(this->verticalAngle > 85.0f)
        this->verticalAngle = 85.0f;
    else if(this->verticalAngle < -85.0f)
        this->verticalAngle = -85.0f;
}