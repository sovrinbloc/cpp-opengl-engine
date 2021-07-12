//
// Created by Joseph Alai on 7/6/21.
//
#include "CameraInput.h"
#include "../RenderEngine/DisplayManager.h"

bool CameraInput::cursorInvisible = false;

double CameraInput::lastX, CameraInput::lastY;
float CameraInput::mouseDX, CameraInput::mouseDY;

Camera *CameraInput::ViewCamera;

bool CameraInput::resetMouse = true;

CameraInput::CameraInput(Camera *camera) {
    ViewCamera = camera;
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
        ViewCamera->ProcessKeyboard(FORWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ViewCamera->ProcessKeyboard(BACKWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ViewCamera->ProcessKeyboard(LEFT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ViewCamera->ProcessKeyboard(RIGHT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        ViewCamera->MovementSpeed = SPEED * 4.5;
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
        ViewCamera->MovementSpeed = SPEED;
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
        ViewCamera->ProcessMouseMovement(CameraInput::mouseDX, CameraInput::mouseDY);
        return;
    }
    CameraInput::resetMouse = true;
}


void CameraInput::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    ViewCamera->ProcessMouseScroll((GLfloat) yoffset);
}