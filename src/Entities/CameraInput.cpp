//
// Created by Joseph Alai on 7/6/21.
//
#include "CameraInput.h"
#include "../RenderEngine/DisplayManager.h"

double lastX, lastY;
float deltaTime;
float lastFrame;
bool firstMouse = true;

Camera *VIEW_CAMERA;

CameraInput::CameraInput(Camera *camera) {
    VIEW_CAMERA  = camera;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &lastX, &lastY);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void CameraInput::move() {
    this->processInput(window);
    uniformMovement();
}

void CameraInput::uniformMovement() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void CameraInput::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        VIEW_CAMERA->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        VIEW_CAMERA->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        VIEW_CAMERA->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        VIEW_CAMERA->ProcessKeyboard(RIGHT, deltaTime);
}


void CameraInput::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (GLfloat) xpos;
        lastY = (GLfloat) ypos;
        firstMouse = false;
    }

    GLfloat xoffset = (GLfloat) xpos - lastX;
    GLfloat yoffset = lastY - (GLfloat) ypos; // reversed since y-coordinates go from bottom to top

    lastX = (GLfloat) xpos;
    lastY = (GLfloat) ypos;

    VIEW_CAMERA->ProcessMouseMovement(xoffset, yoffset);
}

void CameraInput::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    VIEW_CAMERA->ProcessMouseScroll((GLfloat) yoffset);
}