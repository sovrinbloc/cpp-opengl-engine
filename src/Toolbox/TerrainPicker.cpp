//
// Created by Joseph Alai on 7/26/21.
//

#include "TerrainPicker.h"


TerrainPicker::TerrainPicker(Camera *cam, glm::mat4 projection, Terrain *terrain) : camera(cam), terrain(terrain),
                                                                                    MousePicker(cam, projection) {
    this->terrain = terrain;
}

glm::vec3 TerrainPicker::getCurrentTerrainPoint() {
    return currentTerrainPoint;
}

void TerrainPicker::update() {
    viewMatrix = camera->GetViewMatrix();
    currentRay = calculateMouseRay(projectionMatrix, viewMatrix);
    if (intersectionInRange(0, kRayRange, currentRay)) {
        currentTerrainPoint = binarySearch(0, 0, kRayRange, currentRay);
    } else {
        currentTerrainPoint = glm::vec3();
    }
}

glm::vec3 TerrainPicker::binarySearch(int count, float start, float finish, glm::vec3 ray) {
    float half = start + ((finish - start) / 2.0f);
    if (count >= kRecursionCount) {
        glm::vec3 endPoint = getPointOnRay(ray, half, camera);
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

bool TerrainPicker::intersectionInRange(float start, float finish, glm::vec3 ray) {
    glm::vec3 startPoint = getPointOnRay(ray, start, camera);
    glm::vec3 endPoint = getPointOnRay(ray, finish, camera);
    if (!isUnderGround(startPoint) && isUnderGround(endPoint)) {
        return true;
    } else {
        return false;
    }
}


bool TerrainPicker::isUnderGround(glm::vec3 testPoint) {
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
Terrain *TerrainPicker::getTerrain(int x, int y) {
    return terrain;
}
