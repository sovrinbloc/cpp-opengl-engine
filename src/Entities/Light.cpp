//
// Created by Joseph Alai on 7/30/21.
//

#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color, Lighting lighting) : position(position), color(color), lighting(lighting) {}

Lighting Light::getLighting() {
    return lighting;
}

void Light::setLighting(const Lighting &lighting) {
    this->lighting = lighting;
}

glm::vec3 &Light::getPosition() {
    return this->position;
}

void Light::setPosition(glm::vec3 position) {
    this->position = position;
}

void Light::addToPosition(glm::vec3 position) {
    this->position += position;
}

glm::vec3 &Light::getColor() {
    return color;
}

void Light::setColor(glm::vec3 color) {
    this->color = color;
}
