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


class CameraInput : public Camera {
public:
    constexpr static const float kSpeed = 12.5f;
    constexpr static const float kSensitivity = 0.1f;
    constexpr static const float kZoom = 45.0f;
    constexpr static const float kMinZoom = 20.0f;
    constexpr static const float kMaxZoom = 45.0f;

    static double LastMouseX, LastMouseY;
    static float MouseDX, MouseDY;

    static bool ResetMouse;

    // camera options
    static float MovementSpeed;
    static float MouseSensitivity;
    static float Zoom;
    static float ZoomOffset;

    explicit CameraInput(glm::vec3 position = glm::vec3(0.0f, 4.5f, 0.0f));

    void move() override;

    static void toggleCursorStyle();

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow *window);

    static void mouse_callback(GLFWwindow *window, double xPos, double yPos);

    static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    static void ProcessKeyboard(Camera_Movement direction, float deltaTime) ;

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    static void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    static void ProcessMouseScroll(float yOffset);

    virtual void updateCameraVectors();

    static bool cursorInvisible;

};

#endif //ENGINE_CAMERAINPUT_H
