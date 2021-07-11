//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_DISPLAYMANAGER_H
#define CRAFTPROJ_DISPLAYMANAGER_H

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

class DisplayManager {
public:

    static GLint SRC_WIDTH;

    static GLint SRC_HEIGHT;

    static GLFWwindow *window;

    static float delta;

    static float lastFrameTime;

    static int samplers;

    static bool antiAliasingEnabled;

    static int createDisplay();

    static void updateDisplay();

    static bool stayOpen();

    static void closeDisplay();

    static void uniformMovement();

    static float getFrameTimeSeconds();


private:

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};

#endif //CRAFTPROJ_DISPLAYMANAGER_H
