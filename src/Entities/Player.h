//
// Created by Joseph Alai on 7/10/21.
//

#ifndef ENGINE_PLAYER_H
#define ENGINE_PLAYER_H
#include "Entity.h"
#include "../RenderEngine/DisplayManager.h"
class Player : public Entity {
private:
    constexpr static const float RUN_SPEED = 20;
    constexpr static const float TURN_SPEED = 160;

    float currentSpeed = 0.0f;
    float currentTurnSpeed = 0.0f;

public:
    Player(TexturedModel *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
            float scale = 1.0f) : Entity(model, position, rotation, scale){}

    void move();

private:
    void checkInputs();

};
#endif //ENGINE_PLAYER_H
