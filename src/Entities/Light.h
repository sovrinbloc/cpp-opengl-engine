//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "glm/glm.hpp"

using namespace glm;

struct Lighting {
    vec3 attenuation;
    vec3 ambient;
    vec3 diffuse;

    float constant;
    float linear;
    float quadratic;
};

class Light {
private:
    vec3 position;
    vec3 color;
    Lighting lighting;
public:
    explicit Light(vec3 position = vec3(1.2f, 1.0f, 2.0f), vec3 color = vec3(1.0f, 1.0f, 1.0f),
                   Lighting lighting = {
                           .attenuation = glm::vec3(1.0f, 0.0f, 0.0f),
                           .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
                           .diffuse =  glm::vec3(0.5f),
                           .constant = 1.0f,
                           .linear = 0.09f,
                           .quadratic = 0.032f
                   }) : position(position), color(color), lighting(lighting) {
    }

    Lighting getLighting() {
        return lighting;
    }

    void setLighting(const Lighting &lighting) {
        this->lighting = lighting;
    }

    vec3 &getPosition() {
        return this->position;
    }

    void setPosition(vec3 position) {
        this->position = position;
    }

    void addToPosition(vec3 position) {
        this->position += position;
    }

    vec3 & getColor() {
        return color;
    }

    void setColor(vec3 color) {
        this->color = color;
    }
};

#endif //ENGINE_LIGHT_H
