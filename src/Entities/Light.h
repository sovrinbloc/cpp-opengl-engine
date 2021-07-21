//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H

#include "glm/glm.hpp"

struct Lighting {
    glm::vec3 attenuation;
    glm::vec3 ambient;
    glm::vec3 diffuse;

    float constant;
    float linear;
    float quadratic;
};

class Light {
private:
    glm::vec3 position;
    glm::vec3 color;
    Lighting lighting;
public:
    explicit Light(glm::vec3 position = glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
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

    glm::vec3 &getPosition() {
        return this->position;
    }

    void setPosition(glm::vec3 position) {
        this->position = position;
    }

    void addToPosition(glm::vec3 position) {
        this->position += position;
    }

    glm::vec3 & getColor() {
        return color;
    }

    void setColor(glm::vec3 color) {
        this->color = color;
    }

public:
    constexpr static float kDirectional = -1.0f;
};

#endif //ENGINE_LIGHT_H
