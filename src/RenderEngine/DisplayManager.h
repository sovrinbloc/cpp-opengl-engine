//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_DISPLAYMANAGER_H
#define CRAFTPROJ_DISPLAYMANAGER_H

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

extern GLint SRC_WIDTH;
extern GLint SRC_HEIGHT;

extern GLFWwindow *window;

class DisplayManager {
public:

    static float delta;

    static float lastFrameTime;

    static int createDisplay();

    static void updateDisplay();

    static bool stayOpen();

    static void closeDisplay();

    static void uniformMovement();

    static float getFrameTimeSeconds();

    float getPlayerDelta();

    static float getWidth() {
        return SRC_WIDTH;
    }

    static float getHeight() {
        return SRC_HEIGHT;
    }

    static GLFWwindow *getWindow() {
        return window;
    }


private:

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif //CRAFTPROJ_DISPLAYMANAGER_H
