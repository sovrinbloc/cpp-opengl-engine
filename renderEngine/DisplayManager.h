//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_DISPLAYMANAGER_H
#define CRAFTPROJ_DISPLAYMANAGER_H

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include <cstdio>

GLint SRC_WIDTH = 800;
GLint SRC_HEIGHT = 600;

GLFWwindow *window;

class DisplayManager {
public:
    static int createDisplay() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", nullptr, nullptr);
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
    }

    static void updateDisplay() {
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    static bool stayOpen() {
        return !glfwWindowShouldClose(window);
    }

    static void closeDisplay() {
        glfwTerminate();
    }

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

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }
};

#endif //CRAFTPROJ_DISPLAYMANAGER_H
