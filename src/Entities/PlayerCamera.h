//
// Created by Joseph Alai on 7/11/21.
//

#ifndef ENGINE_PLAYERCAMERA_H
#define ENGINE_PLAYERCAMERA_H
#include "Camera.h"
class PlayerCamera : public CameraInput {
public:
    Player *player;

    float distanceFromPlayer = 50.0f;
    float angleAroundPlayer = 0.0f;

    PlayerCamera(Player *player) : player(player), CameraInput(){}

    void move() {
        CameraInput::move();
        calculateAngleAroundPlayer();
        player->move();
        float horizontalDistance = calculateHorizontalDistance();
        float verticalDistance = calculateVerticalDistance();
        calculateCameraPosition(horizontalDistance, verticalDistance);
    }

    void calculateCameraPosition(float horizDistance, float verticDistance) {
        float theta = player->getRotation().y + angleAroundPlayer;
        float offsetX = horizDistance * sin(glm::radians(theta));
        float offsetZ = horizDistance * cos(glm::radians(theta));
        Position.x = player->getPosition().x - offsetX;
        Position.y = player->getPosition().y - verticDistance;
        Position.z = player->getPosition().z - offsetZ;

        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
//            Yaw = 180 - player->getRotation().y + angleAroundPlayer - 90;
            Yaw = 180 - player->getRotation().y + angleAroundPlayer - 90;
        }
        printf("Pitch: %f, Yaw: %f\n", Pitch, Yaw);
    }

    void calculateAngleAroundPlayer(){
        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
            float angleChange = mouseDX * 0.1f;
//            angleAroundPlayer -= angleChange;
        }
    }
private:
    float calculateHorizontalDistance() {
        return (float) (distanceFromPlayer * cos(glm::radians(Pitch + 4)));
    }
    float calculateVerticalDistance() {
        return (float) (distanceFromPlayer * sin(glm::radians(Pitch + 4)));
    }


};
#endif //ENGINE_PLAYERCAMERA_H
