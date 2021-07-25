//
// Created by Joseph Alai on 7/6/21.
//
#include "CameraInput.h"

bool CameraInput::cursorInvisible = false;

double CameraInput::MouseX, CameraInput::MouseY;
double CameraInput::LastMouseX, CameraInput::LastMouseY;
float CameraInput::MouseDX, CameraInput::MouseDY;

// camera options
float CameraInput::MovementSpeed;
float CameraInput::MouseSensitivity;
float CameraInput::Zoom;
float CameraInput::ZoomOffset;

CameraInput::CameraInput(glm::vec3 position) : Camera(position) {
    MovementSpeed = (kSpeed);
    MouseSensitivity = (kSensitivity);
    Zoom = kZoom;
    glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwGetCursorPos(DisplayManager::window, &CameraInput::LastMouseX, &CameraInput::LastMouseY);
    glfwSetCursorPosCallback(DisplayManager::window, mouse_callback);
    glfwSetScrollCallback(DisplayManager::window, scroll_callback);
}

void CameraInput::toggleCursorStyle() {
    cursorInvisible = !cursorInvisible;
    GLint cursorStyle = cursorInvisible ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL;
    glfwSetInputMode(DisplayManager::window, GLFW_CURSOR, cursorStyle);
    DisplayManager::resetMouse = true;
}

void CameraInput::move() {
    this->processInput(DisplayManager::window);
    DisplayManager::uniformMovement();
    updateCameraVectors();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void CameraInput::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        this->toggleCursorStyle();
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        ProcessKeyboard(FORWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ProcessKeyboard(BACKWARD, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ProcessKeyboard(LEFT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ProcessKeyboard(RIGHT, DisplayManager::delta);
    }
    if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
        MovementSpeed = kSpeed * 4.5;
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
        MovementSpeed = kSpeed;
    }
}

void CameraInput::mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    CameraInput::MouseX = xPos;
    CameraInput::MouseY = yPos;
    if (cursorInvisible || glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
        if (DisplayManager::resetMouse) {
            CameraInput::LastMouseX = static_cast<GLfloat>(CameraInput::MouseX);
            CameraInput::LastMouseY = static_cast<GLfloat>(CameraInput::MouseY);
            DisplayManager::resetMouse = false;
        }

        CameraInput::MouseDX = static_cast<GLfloat>(xPos) - static_cast<GLfloat>(CameraInput::LastMouseX);

        // reversed since y-coordinates go from bottom to top
        CameraInput::MouseDY = static_cast<GLfloat>(CameraInput::LastMouseY) - static_cast<GLfloat>(yPos);

        CameraInput::LastMouseX = static_cast<GLfloat>(xPos);
        CameraInput::LastMouseY = static_cast<GLfloat>(yPos);
        ProcessMouseMovement(MouseDX, MouseDY);
        return;
    }
    DisplayManager::resetMouse = true;
}

void CameraInput::scroll_callback(__attribute__((unused)) GLFWwindow *window, __attribute__((unused)) double xOffset, double yOffset) {
    ProcessMouseScroll(static_cast<GLfloat>(yOffset));
}

// processes input received from any keyboard-like input system.
// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void CameraInput::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = CameraInput::MovementSpeed * deltaTime;
    if (direction == FORWARD)
        CameraInput::Position += CameraInput::Front * velocity;
    if (direction == BACKWARD)
        CameraInput::Position -= CameraInput::Front * velocity;
    if (direction == LEFT)
        CameraInput::Position -= CameraInput::Right * velocity;
    if (direction == RIGHT)
        CameraInput::Position += CameraInput::Right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void CameraInput::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;
    Yaw   += xOffset;
    Pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
}

//
/**
 * @brief processes input received from a mouse scroll-wheel event.
 *        Only requires input on the vertical wheel-axis
 *
 *
 * @param yOffset
 */
void CameraInput::ProcessMouseScroll(float yOffset) {
    // zoom in with occlusion with SHIFT
    if (glfwGetKey(DisplayManager::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        Zoom += static_cast<float>(yOffset);
    }
    ZoomOffset = yOffset;
    if (Zoom < kMinZoom)
        Zoom = kMinZoom;
    if (Zoom > kMaxZoom)
        Zoom = kMaxZoom;
}

void CameraInput::updateCameraVectors() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front,
                                      WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));

    printf("right: %f, %f, %f\n", Right.x, Right.y, Right.z);
}