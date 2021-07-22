#include "Player.h"

//
// Created by Joseph Alai on 7/10/21.
//
float Player::SPEED_HACK = 1.0f;

/**
 * @brief move (Main Loop), takes the terrain and moves the character based on the
 *        inputs. It MOVES / ROTATES it on the current terrain. It's utilizing Entity's
 *        information, as well as the DisplayManager to move around.
 * @param terrain
 */
void Player::move(Terrain *terrain) {
    checkInputs();
    rotate(glm::vec3(0.0f, currentTurnSpeed * DisplayManager::getFrameTimeSeconds(), 0.0f));
    float distance = currentSpeed * DisplayManager::getFrameTimeSeconds();
    float dx = distance * sin(glm::radians(getRotation().y));
    float dz = distance * cos(glm::radians(getRotation().y));
    increasePosition(glm::vec3(dx, 0.0f, dz));
    this->upwardsSpeed += kGravity * DisplayManager::getFrameTimeSeconds();
    increasePosition(glm::vec3(0, upwardsSpeed * DisplayManager::getFrameTimeSeconds(), 0.0f));

    float terrainHeight = terrain->getHeightOfTerrain(getPosition().x, getPosition().z);
    if (getPosition().y <= terrainHeight) {
        this->upwardsSpeed = 0.0f;
        setPosition( + glm::vec3(getPosition().x, terrainHeight, getPosition().z));
        this->isInAir = false;
    }
}

void Player::jump() {
    if (!isInAir) {
        this->upwardsSpeed = kJumpPower;
        this->isInAir = true;
    }
}

void Player::checkInputs() {

    if (glfwGetKey(DisplayManager::window, GLFW_KEY_UP) == GLFW_PRESS) {
        this->currentSpeed = kRunSpeed * SPEED_HACK;
    } else if (glfwGetKey(DisplayManager::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        this->currentSpeed = -kRunSpeed * SPEED_HACK;
    } else {
        this->currentSpeed = 0.0f;
    }

    if (glfwGetKey(DisplayManager::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->currentTurnSpeed = -kTurnSpeed * SPEED_HACK / 2;
    } else if (glfwGetKey(DisplayManager::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->currentTurnSpeed = kTurnSpeed * SPEED_HACK / 2;
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