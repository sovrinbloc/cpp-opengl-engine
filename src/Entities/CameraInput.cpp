//
// Created by Joseph Alai on 7/6/21.
//
#include "CameraInput.h"
#include "../RenderEngine/DisplayManager.h"

double CameraInput::lastX, CameraInput::lastY;

Camera *CameraInput::ViewCamera;

bool CameraInput::firstMouse = true;

CameraInput::CameraInput(Camera *camera) {
    ViewCamera = camera;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &CameraInput::lastX, &CameraInput::lastY);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

void CameraInput::move() {
    this->processInput(window);
    DisplayManager::uniformMovement();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void CameraInput::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ViewCamera->ProcessKeyboard(FORWARD, DisplayManager::delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ViewCamera->ProcessKeyboard(BACKWARD, DisplayManager::delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ViewCamera->ProcessKeyboard(LEFT, DisplayManager::delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ViewCamera->ProcessKeyboard(RIGHT, DisplayManager::delta);
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        ViewCamera->MovementSpeed = SPEED * 4.5;
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE) {
        ViewCamera->MovementSpeed = SPEED;
    }
}

void CameraInput::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (CameraInput::firstMouse) {
        CameraInput::lastX = (GLfloat) xpos;
        CameraInput::lastY = (GLfloat) ypos;
        CameraInput::firstMouse = false;
    }

    GLfloat xoffset = (GLfloat) xpos - CameraInput::lastX;
    GLfloat yoffset = CameraInput::lastY - (GLfloat) ypos; // reversed since y-coordinates go from bottom to top

    CameraInput::lastX = (GLfloat) xpos;
    CameraInput::lastY = (GLfloat) ypos;

    ViewCamera->ProcessMouseMovement(xoffset, yoffset);
}

void CameraInput::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ViewCamera->ProcessMouseScroll((GLfloat) yoffset);
}