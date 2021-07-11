//
// Created by Joseph Alai on 7/6/21.
//

#include <cstdio>
#include "DisplayManager.h"
GLint SRC_WIDTH = 800;
GLint SRC_HEIGHT = 600;
GLFWwindow *window;

float DisplayManager::deltaTime;
float DisplayManager::lastFrame;

int DisplayManager::createDisplay() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "ENGINE: Manifest (Alpha & Omega)", nullptr, nullptr);
    if (window == nullptr) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun) framebuffer_size_callback);

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
    DisplayManager::deltaTime = currentFrame - DisplayManager::lastFrame;
    DisplayManager::lastFrame = currentFrame;
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
}