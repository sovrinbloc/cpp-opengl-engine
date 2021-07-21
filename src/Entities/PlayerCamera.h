//
// Created by Joseph Alai on 7/11/21.
//

#ifndef ENGINE_PLAYERCAMERA_H
#define ENGINE_PLAYERCAMERA_H
#include "Camera.h"
#include "CameraInput.h"

class PlayerCamera : public CameraInput {
public:
    Player *player;

    float distanceFromPlayer = 55.0f;
    float angleAroundPlayer = 0.0f;

    explicit PlayerCamera(Player *player) : player(player), CameraInput(){
        Pitch = -20.0f;
    }

    void move(Terrain *terrain);

    void calculateCameraPosition(float horizDistance, float verticDistance) const;

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() override;

    void calculateAngleAroundPlayer();
private:
    float calculateHorizontalDistance() const;
    float calculateVerticalDistance() const;

    void updateCameraVectors() override;

    void calculateZoom();


};
#endif //ENGINE_PLAYERCAMERA_H
