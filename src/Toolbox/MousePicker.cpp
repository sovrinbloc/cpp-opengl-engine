//
// Created by Joseph Alai on 7/21/21.
//

#include "MousePicker.h"

MousePicker::MousePicker(Camera *cam, glm::mat4 projection) : camera(cam) {
    viewMatrix = camera->GetViewMatrix();
    projectionMatrix = projection;
}

glm::vec3 MousePicker::getCurrentRay() {
    return currentRay;
}

void MousePicker::update() {
    viewMatrix = camera->GetViewMatrix();
    currentRay = calculateMouseRay(projectionMatrix, viewMatrix);
}

glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance, Camera *camera) {
    glm::vec3 camPos = camera->Position;
    glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
    glm::vec3 scaledRay =  glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
    return (start + scaledRay);
}

