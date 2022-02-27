//
// Created by Joseph Alai on 2/25/22.
//

#include "UiConstraints.h"

UiConstraints::UiConstraints(float x, float y, float width, float height) : position(glm::vec2(x,y)), size(glm::vec2(width, height)) {}

UiConstraints::UiConstraints(glm::vec2 position, glm::vec2 size) : position(position), size(size) {}

float UiConstraints::getX() const {
    return UiConstraints::position.x;
}

void UiConstraints::setX(float x) {
    UiConstraints::position.x = x;
}

float UiConstraints::getY() const {
    return UiConstraints::position.y;
}

void UiConstraints::setY(float y) {
    UiConstraints::position.y = y;
}

float UiConstraints::getWidth() const {
    return UiConstraints::size.x;
}

void UiConstraints::setWidth(float width) {
    size.x = width;
}

float UiConstraints::getHeight() const {
    return UiConstraints::size.y;
}

void UiConstraints::setHeight(float height) {
    size.y = height;
}

UiConstraints::UiConstraints() {}

const glm::vec2 &UiConstraints::getPosition() const {
    return position;
}

void UiConstraints::setPosition(const glm::vec2 &position) {
    UiConstraints::position = position;
}

const glm::vec2 &UiConstraints::getSize() const {
    return size;
}

void UiConstraints::setSize(const glm::vec2 &size) {
    UiConstraints::size = size;
}
