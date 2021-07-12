//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_CAMERAINPUT_H
#define ENGINE_CAMERAINPUT_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "Camera.h"

class CameraInput : public Camera {
public:
    static double lastX, lastY;
    static float mouseDX, mouseDY;

    static bool resetMouse;

    explicit CameraInput(glm::vec3 position = glm::vec3(0.0f, 4.5f, 0.0f));

    void move();

    static void toggleCursorStyle();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window);

    static void mouse_callback (GLFWwindow *window, double xpos, double ypos);

    static void scroll_callback (GLFWwindow *window, double xoffset, double yoffset);

private:
    static bool cursorInvisible;
};

#endif //ENGINE_CAMERAINPUT_H
