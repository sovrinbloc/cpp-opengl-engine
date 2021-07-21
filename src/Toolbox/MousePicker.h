//
// Created by Joseph Alai on 7/21/21.
//

#ifndef ENGINE_MOUSEPICKER_H
#define ENGINE_MOUSEPICKER_H

#include "glm/glm.hpp"
#include "../Entities/Camera.h"
#include "../Entities/CameraInput.h"

/**
 * Based on the OpenGL ThinMatrix Tutorial and ...
 * https://antongerdelan.net/opengl/raycasting.html
 */
class MousePicker {
private:
    constexpr static int kRecursionCount = 200;
    constexpr static float kRayRange = 200;

    glm::vec3 currentRay;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    Camera *camera;

    Terrain *terrain;
    glm::vec3 currentTerrainPoint;

public:
    MousePicker(Camera *cam, glm::mat4 projection, Terrain *terrain);
    glm::vec3 getCurrentTerrainPoint();
    glm::vec3 getCurrentRay();
    void update();

private:
    glm::vec3 calculateMouseRay();
    glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
    glm::vec4 toEyeCoords(glm::vec4 clipCoords);

    Terrain *getTerrain(int x, int y);

    glm::vec2 getNormalizedDeviceCoords();
    glm::vec3 getPointOnRay(glm::vec3 ray, float distance);
    glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray);
    bool intersectionInRange(float start, float finish, glm::vec3 ray);
    bool isUnderGround(glm::vec3 testPoint);
};


#endif //ENGINE_MOUSEPICKER_H
