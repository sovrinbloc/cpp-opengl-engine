//
// Created by Joseph Alai on 7/10/21.
//

#ifndef ENGINE_PLAYER_H
#define ENGINE_PLAYER_H
#include "Entity.h"
#include "../RenderEngine/DisplayManager.h"
#include "../Terrain/Terrain.h"
class Player : public Entity {
private:
    static float SPEED_HACK;
    constexpr static const float RUN_SPEED = 20;
    constexpr static const float TURN_SPEED = 160;
    constexpr static const float GRAVITY = -50;
    constexpr static const float JUMP_POWER = 30;

    constexpr static const float TERRAIN_HEIGHT = 0;

    float currentSpeed = 0.0f;
    float currentTurnSpeed = 0.0f;
    float upwardsSpeed = 0;
    bool isInAir = false;

    void jump();

public:
    Player(TexturedModel *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
            float scale = 1.0f) : Entity(model, position, rotation, scale){}

    void move(Terrain *terrain);

private:
    void checkInputs();

};
#endif //ENGINE_PLAYER_H
