//
// Created by Joseph Alai on 7/21/21.
//

#include "MousePicker.h"

MousePicker::MousePicker(Camera *cam, glm::mat4 projection) : camera(cam), projectionMatrix(projection) {
    viewMatrix = camera->GetViewMatrix();
}

glm::vec3 MousePicker::getCurrentRay() {
    return currentRay;
}

void MousePicker::update() {
    viewMatrix = camera->GetViewMatrix();
    currentRay = calculateMouseRay();
}

glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY) {
    float x = (2.0f * mouseX) / DisplayManager::SRC_WIDTH - 1;
    float y = (2.0f * mouseY) / DisplayManager::SRC_HEIGHT - 1;
    return glm::vec2(x, -y);
}

glm::vec3 MousePicker::calculateMouseRay() {
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords((float)CameraInput::LastMouseX, (float)CameraInput::LastMouseY);
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = toEyeCoords(clipCoords);
    glm::vec3 worldCoords = toWorldCoords(eyeCoords);
    return worldCoords;
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords) {
    glm::vec4 invertedProjection = glm::inverse(projectionMatrix) * clipCoords;
    return glm::vec4(invertedProjection.x, invertedProjection.y, -1.0f, 0.0f);
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords) {
    glm::vec3 rayWorld = glm::inverse(viewMatrix) * eyeCoords;
    return glm::normalize(rayWorld);
}
