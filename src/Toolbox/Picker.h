//
// Created by Joseph Alai on 7/26/21.
//

#ifndef ENGINE_PICKER_H
#define ENGINE_PICKER_H

#include "glm/glm.hpp"
#include "../Entities/Camera.h"
#include "Color.h"
/**
 * Overview
 * It can be useful to click on, or "pick" a 3d object in our scene using the mouse cursor. One way of doing this is to
 * project a 3d ray from the mouse, through the camera, into the scene, and then check if that ray intersects with any
 * objects. This is usually called ray casting. This is an entirely mathematical exercise - we don't use any OpenGL code
 * or draw any graphics - this means that it will apply to any 3d application the same way. The mathematical subject is
 * usually called geometric intersection testing.
 */
class Picker {
public:
    static glm::vec3 calculateMouseRay(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

    static Color getColor();

private:

    static glm::vec3 toWorldCoords(glm::vec4 eyeCoords, glm::mat4 viewMatrix);

    static glm::vec4 toEyeCoords(glm::vec4 clipCoords, glm::mat4 projectionMatrix);

    static glm::vec2 getNormalizedDeviceCoords();

};

#endif //ENGINE_PICKER_H
