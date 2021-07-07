//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_CAMERAINPUT_H
#define ENGINE_CAMERAINPUT_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "Camera.h"

extern double lastX, lastY;
extern float deltaTime;
extern float lastFrame;
extern bool firstMouse;
extern Camera *VIEW_CAMERA;

class CameraInput {
public:

    CameraInput(Camera *camera);

    void move();

    static void uniformMovement();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window);

    static Camera *getCamera() {
        return VIEW_CAMERA;
    }

    static void mouse_callback (GLFWwindow *window, double xpos, double ypos);

    static void scroll_callback (GLFWwindow *window, double xoffset, double yoffset);
};

#endif //ENGINE_CAMERAINPUT_H
