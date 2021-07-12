//
// Created by Joseph Alai on 7/6/21.
//
#include "CameraInput.h"
#include "../RenderEngine/DisplayManager.h"

bool CameraInput::cursorInvisible = false;

double CameraInput::lastX, CameraInput::lastY;
float CameraInput::mouseDX, CameraInput::mouseDY;

bool CameraInput::resetMouse = true;

CameraInput::CameraInput(glm::vec3 position) : Camera(position) {
    glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwGetCursorPos(DisplayManager::window, &CameraInput::lastX, &CameraInput::lastY);
    glfwSetCursorPosCallback(DisplayManager::window, mouse_callback);
    glfwSetScrollCallback(DisplayManager::window, scroll_callback);
}

void CameraInput::toggleCursorStyle() {
    cursorInvisible = !cursorInvisible;
    GLint cursorStyle = cursorInvisible ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, cursorStyle);
    resetMouse = true;
}

void CameraInput::move() {
    this->processInput(DisplayManager::window);
    DisplayManager::uniformMovement();
    Camera::move();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void CameraInput::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        this->toggleCursorStyle();
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        ProcessKeyboard(FORWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ProcessKeyboard(BACKWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ProcessKeyboard(LEFT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ProcessKeyboard(RIGHT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        MovementSpeed = SPEED * 4.5;
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
        MovementSpeed = SPEED;
    }
}

void CameraInput::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (cursorInvisible || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
        if (CameraInput::resetMouse) {
            CameraInput::lastX = (GLfloat) xpos;
            CameraInput::lastY = (GLfloat) ypos;
            CameraInput::resetMouse = false;
        }

        CameraInput::mouseDX = (GLfloat) xpos - (GLfloat) CameraInput::lastX;

        // reversed since y-coordinates go from bottom to top
        CameraInput::mouseDY = (GLfloat) CameraInput::lastY - (GLfloat) ypos;

        CameraInput::lastX = (GLfloat) xpos;
        CameraInput::lastY = (GLfloat) ypos;
        ProcessMouseMovement(mouseDX, mouseDY);
        return;
    }
    CameraInput::resetMouse = true;
}


void CameraInput::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ProcessMouseScroll((GLfloat) yoffset);
}