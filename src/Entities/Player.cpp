#include "Player.h"

//
// Created by Joseph Alai on 7/10/21.
//
float Player::SPEED_HACK = 1.0f;

void Player::move(Terrain *terrain) {
    checkInputs();
    rotate(glm::vec3(0.0f, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0.0f));
    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = distance * sin(glm::radians(getRotation().y));
    float dz = distance * cos(glm::radians(getRotation().y));
    increasePosition(glm::vec3(dx, 0.0f, dz));
    this->upwardsSpeed += GRAVITY * DisplayManager::getFrameTimeSeconds();
    increasePosition(glm::vec3(0, upwardsSpeed * DisplayManager::getFrameTimeSeconds(), 0.0f));
//    printf("%f, %f, %f\n", getPosition().x, getPosition().y, getPosition().z);

    float terrainHeight = terrain->getHeightOfTerrain(getPosition().x, getPosition().z);
    if (getPosition().y <= terrainHeight) {
        this->upwardsSpeed = 0.0f;
        setPosition( + glm::vec3(getPosition().x, terrainHeight, getPosition().z));
        this->isInAir = false;
    }
}

void Player::jump() {
    if (!isInAir) {
        this->upwardsSpeed = JUMP_POWER;
        this->isInAir = true;
    }
}

void Player::checkInputs() {

    if (glfwGetKey(DisplayManager::window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->currentSpeed = RUN_SPEED * SPEED_HACK;
    } else if (glfwGetKey(DisplayManager::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->currentSpeed = -RUN_SPEED * SPEED_HACK;
    } else {
        this->currentSpeed = 0.0f;
    }

    if (glfwGetKey(DisplayManager::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->currentTurnSpeed = -TURN_SPEED * SPEED_HACK / 2;
    } else if (glfwGetKey(DisplayManager::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->currentTurnSpeed = TURN_SPEED * SPEED_HACK / 2;
    } else {
        this->currentTurnSpeed = 0.0f;
    }

    if (glfwGetKey(DisplayManager::window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->jump();
    }


    if (glfwGetKey(DisplayManager::window, GLFW_KEY_TAB) == GLFW_PRESS) {
        SPEED_HACK = 4.5f;
    }
    if (glfwGetKey(DisplayManager::window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
        SPEED_HACK = 1.0f;
    }
}