//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_INPUTMANAGER_H
#define ENGINE_INPUTMANAGER_H
#include "definitions.h"
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "entities/Camera.h"

double lastX = SRC_WIDTH / 2.0f;
double lastY = SRC_HEIGHT / 2.0f;

// timing
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

class InputManager {
public:
    static void configureInput() {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwGetCursorPos(window, &lastX, &lastY);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
    }

    static void enableInput() {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
    }
private:
    static void processInput(GLFWwindow *window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
            glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(yoffset);
    }
};

#endif //ENGINE_INPUTMANAGER_H
