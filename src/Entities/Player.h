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
    constexpr static const float kRunSpeed = 20;
    constexpr static const float kTurnSpeed = 160;
    constexpr static const float kGravity = -50;
    constexpr static const float kJumpPower = 30;

    constexpr static const float kTerrainHeight = 0;

    float currentSpeed = 0.0f;
    float currentTurnSpeed = 0.0f;
    float upwardsSpeed = 0;
    bool isInAir = false;

    void jump();

public:
    /**
     * @brief Player extends Entity: so it stores TexturedModel, as well as its' vectors
     *        to be able to manipulate the model. It also checks for input, and allows
     *        the user to move around, zoom in and out, etc.
     * @param model
     * @param position
     * @param rotation
     * @param scale
     */
    Player(TexturedModel *model, BoundingBox *box, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
            float scale = 1.0f) : Entity(model, box, position, rotation, scale){}

    void move(Terrain *terrain);

private:
    void checkInputs();

};
#endif //ENGINE_PLAYER_H
