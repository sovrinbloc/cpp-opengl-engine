//
// Created by Joseph Alai on 7/10/21.
//
#include "Player.h"

void Player::move() {
    checkInputs();
    rotate(glm::vec3(0.0f, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0.0f));
    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = distance * sin(glm::radians(getRotation().y));
    float dz = distance * cos(glm::radians(getRotation().y));
    increasePosition(glm::vec3(dx, 0.0f, dz));
}

void Player::checkInputs() {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->currentSpeed = RUN_SPEED;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->currentSpeed = -RUN_SPEED;
    } else {
        this->currentSpeed = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->currentTurnSpeed = -TURN_SPEED;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->currentTurnSpeed = TURN_SPEED;
    } else {
        this->currentTurnSpeed = 0.0f;
    }
}