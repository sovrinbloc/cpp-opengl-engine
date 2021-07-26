//
// Created by Joseph Alai on 7/26/21.
//
#include "InputMaster.h"
#include "../RenderEngine/DisplayManager.h"

    bool InputMaster::pendingClick;

    bool InputMaster::pendingButton;

    ClickButtons InputMaster::lastClick;

    KeyboardKeys InputMaster::lastButton;

    std::vector<KeyboardKeys> InputMaster::pressedKeys;

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
    if ( std::find(pressedKeys.begin(), pressedKeys.end(), key) != pressedKeys.end() ) {
        return true;
    }
    return false;
}