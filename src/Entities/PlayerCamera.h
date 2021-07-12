//
// Created by Joseph Alai on 7/11/21.
//

#ifndef ENGINE_PLAYERCAMERA_H
#define ENGINE_PLAYERCAMERA_H
#include "Camera.h"
#include "glm/gtx/quaternion.hpp"
class PlayerCamera : public CameraInput {
public:
    Player *player;

    float distanceFromPlayer = 55.0f;
    float angleAroundPlayer = 0.0f;

    PlayerCamera(Player *player) : player(player), CameraInput(){
        Pitch = -20.0f;
    }

    void move() {
        this->processInput(DisplayManager::window);
        DisplayManager::uniformMovement();
        updateCameraVectors();
        calculateZoom();
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
        Position.z = player->getPosition().z - offsetZ;
        Position.y = player->getPosition().y - verticDistance + 4;

        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            Yaw = int(180 - player->getRotation().y + angleAroundPlayer - 90) % 360;
        }
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() {
        glm::vec3  front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        return glm::lookAt(this->Position, player->getPosition(), this->Up);
    }

    void calculateAngleAroundPlayer(){
        if (glfwGetMouseButton(DisplayManager::window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            float angleChange = mouseDX * 0.1f;
            angleAroundPlayer -= angleChange;
        }
    }
private:
    float calculateHorizontalDistance() {
        return (float) (distanceFromPlayer * cos(glm::radians(Pitch + 4)));
    }
    float calculateVerticalDistance() {
        return (float) (distanceFromPlayer * sin(glm::radians(Pitch + 4)));
    }

    void updateCameraVectors() {
        Front = glm::vec3(0, 0, 1);
        Up = glm::vec3(0, 1, 0);
        Right = glm::vec3(1, 0, 0);
    }

    void updateCameraVectorsQuaternions() {
        glm::quat Orientation;
        Yaw = abs(Yaw);
        glm::quat rotation = glm::quat(glm::vec3(Yaw, Pitch, Roll));

        Orientation = rotation * Orientation;
        Orientation = glm::normalize(Orientation);
        glm::mat4 OrientMat = glm::mat4_cast(Orientation);

        glm::mat4 viewMatrix = OrientMat;
        viewMatrix = glm::transpose(viewMatrix);

        Front = glm::vec3(viewMatrix[2]);
        Up = glm::vec3(viewMatrix[1]);
        Right = glm::vec3(viewMatrix[0]);
    }

    void calculateZoom(){
        float zoomLevel = ZoomOffset * 0.03f;
        distanceFromPlayer -= zoomLevel;
        if(distanceFromPlayer<5){
            distanceFromPlayer = 5;
        }
    }


};
#endif //ENGINE_PLAYERCAMERA_H
