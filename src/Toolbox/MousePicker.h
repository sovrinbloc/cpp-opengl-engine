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
    glm::vec3 currentRay;

    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;

    Camera *camera;

public:
    MousePicker(Camera *cam, glm::mat4 projection);
    glm::vec3 getCurrentRay();
    void update();
    glm::vec3 calculateMouseRay();
    glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
    glm::vec4 toEyeCoords(glm::vec4 clipCoords);
    glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
};


#endif //ENGINE_MOUSEPICKER_H
