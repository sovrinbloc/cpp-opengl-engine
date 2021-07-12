//
// Created by Joseph Alai on 7/11/21.
//

#ifndef ENGINE_PLAYERCAMERA_H
#define ENGINE_PLAYERCAMERA_H
#include "Camera.h"
class PlayerCamera : CameraInput {
public:
    Player *player;

    float distanceFromPlayer = 50.0f;
    float angleAroundPlayer = 0.0f;

    PlayerCamera(Player *player, Camera *camera) : player(player), CameraInput(camera){}

    void move() {
        this->processInput(DisplayManager::window);
        DisplayManager::uniformMovement();
        calculateAngleAroundPlayer();
        getCamera()->move();
        player->move();
        float horizontalDistance = calculateHorizontalDistance();
        float verticalDistance = calculateVerticalDistance();
        calculateCameraPosition(horizontalDistance, verticalDistance);
    }

    void calculateCameraPosition(float horizDistance, float verticDistance) {
        float theta = player->getRotation().y + angleAroundPlayer;
        float offsetX = horizDistance * sin(glm::radians(theta));
        float offsetZ = horizDistance * cos(glm::radians(theta));
        getCamera()->Position.x = player->getPosition().x - offsetX;
        getCamera()->Position.y = player->getPosition().y - verticDistance;
        getCamera()->Position.z = player->getPosition().z - offsetZ;

        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
            getCamera()->Yaw = 180 - player->getRotation().y + angleAroundPlayer - 90;
        }
        printf("Pitch: %f, Yaw: %f\n", getCamera()->Pitch, getCamera()->Yaw);
    }

    void calculateAngleAroundPlayer(){
        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS) {
            float angleChange = mouseDX * 0.1f;
//            angleAroundPlayer -= angleChange;
        }
    }
private:
    float calculateHorizontalDistance() {
        return (float) (distanceFromPlayer * cos(glm::radians(getCamera()->Pitch)));
    }
    float calculateVerticalDistance() {
        return (float) (distanceFromPlayer * sin(glm::radians(getCamera()->Pitch)));
    }


};
#endif //ENGINE_PLAYERCAMERA_H
