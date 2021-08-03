//
// Created by Joseph Alai on 7/26/21.
//

#ifndef ENGINE_PICKER_H
#define ENGINE_PICKER_H

#include "glm/glm.hpp"
#include "../Entities/Camera.h"
#include "Color.h"
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
