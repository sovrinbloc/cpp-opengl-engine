//
// Created by Joseph Alai on 7/6/21.
//

#include <cstdio>
#include "DisplayManager.h"
GLint DisplayManager::SRC_WIDTH = 800;
GLint DisplayManager::SRC_HEIGHT = 600;
GLFWwindow *DisplayManager::window;

float DisplayManager::delta;
float DisplayManager::lastFrameTime;
bool DisplayManager::resetMouse = true;

int DisplayManager::createDisplay() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(Width(), Height(), "GAME ENGINE: Manifest (Alpha & Omega)", nullptr, nullptr);
    if (window == nullptr) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glEnable(GL_MULTISAMPLE);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#ifndef __APPLE__
    if (glewInit() != GLEW_OK) {
            return -1;
        }
#endif

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    return 1;
}

void DisplayManager::updateDisplay() {
    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);

    glfwPollEvents();
}

void DisplayManager::uniformMovement() {
    float currentFrame = glfwGetTime();
    delta = currentFrame - lastFrameTime;
    lastFrameTime = currentFrame;
}

float DisplayManager::getFrameTimeSeconds() {
    return delta;
}

bool DisplayManager::stayOpen() {
    return !glfwWindowShouldClose(window);
}

void DisplayManager::closeDisplay() {
    glfwTerminate();
}

void DisplayManager::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    updatePerspective(width, height);
    resetMouse = false;
}

GLint &DisplayManager::Width() {
    return SRC_WIDTH;
}

GLint &DisplayManager::Height() {
    return SRC_HEIGHT;
}

void DisplayManager::updatePerspective(int width, int height) {
    DisplayManager::Width() = static_cast<GLint>(width);
    DisplayManager::Height() = static_cast<GLint>(height);
}
