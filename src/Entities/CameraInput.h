//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_CAMERAINPUT_H
#define ENGINE_CAMERAINPUT_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "Camera.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float SPEED = 12.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float MIN_ZOOM = 20.0f;
const float MAX_ZOOM = 45.0f;

class CameraInput : public Camera {
public:
    static double lastX, lastY;
    static float mouseDX, mouseDY;

    static bool resetMouse;

    // camera options
    static float MovementSpeed;
    static float MouseSensitivity;
    static float Zoom;
    static float ZoomOffset;

    explicit CameraInput(glm::vec3 position = glm::vec3(0.0f, 4.5f, 0.0f));

    virtual void move();

    static void toggleCursorStyle();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window);

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    static void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    static void ProcessMouseScroll(float yoffset);

    void toggleFirstPersonShooter(bool enabled);

    void ToggleChangeSpeed(float velocity) {
        this->MovementSpeed = velocity;
    }

    virtual void updateCameraVectors();

    static bool cursorInvisible;
private:

    bool fps = false;
};

#endif //ENGINE_CAMERAINPUT_H
