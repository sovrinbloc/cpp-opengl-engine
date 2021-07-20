//
// Created by Joseph Alai on 7/20/21.
//

#ifndef ENGINE_LIGHUTIL_H
#define ENGINE_LIGHUTIL_H

#include "glm/glm.hpp"

class LightUtil {
public:
    static glm::vec3 AttenuationDistance(int distance) {
        if (distance <= 7) {
            return glm::vec3(1.0f, 0.7f, 1.8f);
        } else if (distance <= 13) {
            return glm::vec3(1.0f, 0.35, 0.44f);
        } else if (distance <= 20) {
            return glm::vec3(1.0f, 0.22f, 0.20f);
        } else if (distance <= 32) {
            return glm::vec3(1.0f, 0.14f, 0.07f);
        } else if (distance <= 50) {
            return glm::vec3(1.0f, 0.09f, 0.032f);
        } else if (distance <= 65) {
            return glm::vec3(1.0f, 0.07f, 0.017f);
        } else if (distance <= 100) {
            return glm::vec3(1.0f, 0.045f, 0.0075f);
        } else if (distance <= 160) {
            return glm::vec3(1.0f, 0.027f, 0.0028f);
        } else if (distance <= 200) {
            return glm::vec3(1.0f, 0.022f, 0.0019f);
        } else if (distance <= 325) {
            return glm::vec3(1.0f, 0.014f, 0.0007f);
        } else if (distance <= 600) {
            return glm::vec3(1.0f, 0.007f, 0.0002f);
        } else {
            return glm::vec3(1.0f, 0.0014f, 0.000007f);
        }
    }
};

#endif //ENGINE_LIGHUTIL_H
