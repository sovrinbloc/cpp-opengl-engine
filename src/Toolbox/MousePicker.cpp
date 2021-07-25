//
// Created by Joseph Alai on 7/21/21.
//

#include "MousePicker.h"

MousePicker::MousePicker(Camera *cam, glm::mat4 projection, Terrain *terrain) : camera(cam), projectionMatrix(projection), terrain(terrain) {
    viewMatrix = camera->GetViewMatrix();
    projectionMatrix = projection;
    this->terrain = terrain;
}

glm::vec3 MousePicker::getCurrentTerrainPoint() {
    return currentTerrainPoint;
}

glm::vec3 MousePicker::getCurrentRay() {
    return currentRay;
}

void MousePicker::update() {
    viewMatrix = camera->GetViewMatrix();
    currentRay = calculateMouseRay();
    if (intersectionInRange(0, kRayRange, currentRay)) {
        currentTerrainPoint = binarySearch(0, 0, kRayRange, currentRay);
    } else {
        currentTerrainPoint = glm::vec3();
    }
}

glm::vec3 MousePicker::calculateMouseRay() {
    glm::vec2 normalizedCoords = getNormalizedDeviceCoords();
    glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
    glm::vec4 eyeCoords = toEyeCoords(clipCoords);
    glm::vec3 worldCoords = toWorldCoords(eyeCoords);
    return worldCoords;
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords) {
    glm::vec3 rayWorld = glm::inverse(viewMatrix) * eyeCoords;
    return glm::normalize(rayWorld);
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords) {
    glm::vec4 invertedProjection = glm::inverse(projectionMatrix) * clipCoords;
    return glm::vec4(invertedProjection.x, invertedProjection.y, -1.0f, 0.0f);
}

glm::vec2 MousePicker::getNormalizedDeviceCoords() {
    float x = (2.0f * static_cast<float>(CameraInput::MouseX)) / static_cast<float>(DisplayManager::Width()) - 1;
    float y = (2.0f * static_cast<float>(CameraInput::MouseY)) / static_cast<float>(DisplayManager::Height()) - 1;
    return glm::vec2(x, -y);
}

glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance) {
    glm::vec3 camPos = camera->Position;
    glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
    glm::vec3 scaledRay =  glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
    return (start + scaledRay);
}

glm::vec3 MousePicker::binarySearch(int count, float start, float finish, glm::vec3 ray) {
    float half = start + ((finish - start) / 2.0f);
    if (count >= kRecursionCount) {
        glm::vec3 endPoint = getPointOnRay(ray, half);
        Terrain *terrain = getTerrain(endPoint.x, endPoint.z);
        if (terrain != nullptr) {
            return endPoint;
        } else {
            return glm::vec3();
        }
    }
    if (intersectionInRange(start, half, ray)) {
        return binarySearch(count + 1, start, half, ray);
    } else {
        return binarySearch(count + 1, half, finish, ray);
    }
}

bool MousePicker::intersectionInRange(float start, float finish, glm::vec3 ray) {
    glm::vec3 startPoint = getPointOnRay(ray, start);
    glm::vec3 endPoint = getPointOnRay(ray, finish);
    if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
        return true;
    } else {
        return false;
    }
}

// TODO: replace with (x, y) to allow for an array of terrains, so we can swap through them.
/**
 * @brief example to add multiple terrains:
 *        int x = worldX / Terrain.size();
 *        int z = worldZ / Terrain.size();
 *        return terrains[x][z]
 *
 * @param x
 * @param y
 * @return
 */
Terrain *MousePicker::getTerrain(int x, int y) {
    return terrain;
}

bool MousePicker::isUnderGround(glm::vec3 testPoint) {
    Terrain *terrain = getTerrain(testPoint.x, testPoint.z);
    float height = 0;
    if (terrain != nullptr) {
        height = terrain->getHeightOfTerrain(testPoint.x, testPoint.z);
    }
    if (testPoint.y < height) {
        return true;
    } else {
        return false;
    }
}
