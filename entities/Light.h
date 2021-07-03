//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H
#include "glm/glm.hpp"
using namespace glm;
class Light {
private:
    vec3 position;
    vec3 color;
public:
    Light(const vec3 &position, const vec3 &color) : position(position), color(color) {}

    const vec3 &getPosition() const {
        return position;
    }

    void setPosition(const vec3 &position) {
        Light::position = position;
    }

    const vec3 &getColor() const {
        return color;
    }

    void setColor(const vec3 &color) {
        Light::color = color;
    }
};
#endif //ENGINE_LIGHT_H
