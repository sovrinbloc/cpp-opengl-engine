//
// Created by Joseph Alai on 7/26/21.
//
#include "InputMaster.h"
#include "../RenderEngine/DisplayManager.h"
#include "../Toolbox/Picker.h"

bool InputMaster::pendingClick;

bool InputMaster::pendingButton;

ClickButtons InputMaster::lastClick;

KeyboardKeys InputMaster::lastButton;

std::vector<KeyboardKeys> InputMaster::pressedKeys;

double InputMaster::mouseX, InputMaster::mouseY;

double InputMaster::lastMouseX, InputMaster::lastMouseY;

float InputMaster::mouseDx, InputMaster::mouseDy;


void InputMaster::init() {
    glfwSetKeyCallback(DisplayManager::window, key_callback);
    glfwSetMouseButtonCallback(DisplayManager::window, mouse_callback);
}

bool InputMaster::hasPendingClick() {
    if (pendingClick) {
        return true;
    }
    return false;
}

bool InputMaster::hasPendingButton() {
    if (pendingButton) {
        return true;
    }
    return false;
}

bool InputMaster::buttonPressed(KeyboardKeys key) {
    if (lastButton == key) {
        return true;
    }
    return false;
}

bool InputMaster::mouseClicked(ClickButtons button) {
    if (lastClick == button) {
        return true;
    }
    return false;
}

int InputMaster::lastTyped() {
    return lastButton;
}

int InputMaster::lastClicked() {
    return lastClick;
}

void InputMaster::clearKeys() {
    lastButton = Unknown;
}

void InputMaster::setKey(KeyboardKeys key) {
    pendingButton = true;
    lastButton = key;
}

void InputMaster::setClick(ClickButtons button) {
    pendingClick = true;
    lastClick = button;
}

void InputMaster::resetClick() {
    lastClick = Nothing;
}

void InputMaster::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {}
    setKey(static_cast<KeyboardKeys>(key));
}

void InputMaster::mouse_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {}
    if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS) {}
    setClick(static_cast<ClickButtons>(button));
}

void InputMaster::clearKey(KeyboardKeys key) {
    pressedKeys.erase(std::remove(pressedKeys.begin(), pressedKeys.end(), key), pressedKeys.end());
}

bool InputMaster::findKey(KeyboardKeys key) {
    if (std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end()) {
        return true;
    }
    return false;
}

bool InputMaster::isKeyDown(KeyboardKeys key) {
    return glfwGetKey(DisplayManager::window, key) == GLFW_PRESS;
}

bool InputMaster::isMouseDown(ClickButtons click) {
    return glfwGetMouseButton(DisplayManager::window, click) == GLFW_PRESS;
}

glm::vec3 InputMaster::getClicked(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    if (InputMaster::hasPendingClick()) {
        if (InputMaster::mouseClicked(LeftClick)) {
            unsigned char pixel[3];
            glFlush();
            glFinish();
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT, viewport);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            glm::vec3 out = Picker::calculateMouseRay(projectionMatrix, viewMatrix);

            glReadPixels(static_cast<int>(mouseX), static_cast<int>(static_cast<float>(DisplayManager::Height()) - mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
            glm::vec3 colors = glm::vec3(pixel[0], pixel[1], pixel[2]);
            printf("1 color.x, color.y, color.z: (%f, %f, %f)\n", colors.x, colors.y, colors.z); // OK

//            printf("color.x, color.y, color.z: (%f, %f, %f)\n", colors.x, colors.y, colors.z);

//            glReadPixels(mouseX, (viewport[3] - mouseY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
//            glReadPixels(static_cast<GLint>(InputMaster::mouseX), static_cast<GLint>(DisplayManager::Height() - InputMaster::mouseY) - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &pixel);

            return colors;
        }
    }
    return glm::vec3(-1.0f);
}
