//
// Created by Joseph Alai on 7/10/21.
//

#ifndef ENGINE_PLAYER_H
#define ENGINE_PLAYER_H
#include "Entity.h"
class Player : public Entity {
private:
    static const float RUN_SPEED = 20;
    static const float TURN_SPEED = 160;
    float currentSpeed = 0.0f;
    float currentTurnSpeed = 0.0f;

public:
    Player(TexturedModel *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
            float scale = 1.0f) : Entity(model(model), position(position), rotation(rotation), scale(scale)){}

    void move() {
        checkInputs();
        rotate(rotation);
    }

private:
    checkInputs() {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)) {
            this->currentSpeed = RUN_SPEED;
        } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)) {
            this->currentSpeed = -RUN_SPEED;
        } else {
            this->currentSpeed = 0.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)) {
            this->currentTurnSpeed = -TURN_SPEED;
        } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)) {
            this->currentTurnSpeed = TURN_SPEED;
        } else {
            this->currentTurnSpeed = 0.0f;
        }
    }




};
#endif //ENGINE_PLAYER_H
