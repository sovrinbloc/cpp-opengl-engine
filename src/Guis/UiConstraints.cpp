//
// Created by Joseph Alai on 2/25/22.
//

#include "UiConstraints.h"

UiConstraints::UiConstraints(int x, int y, int width, int height) : position(glm::ivec2(x,y)), size(glm::ivec2(width, height)) {}

UiConstraints::UiConstraints(glm::ivec2 position, glm::ivec2 size) : position(position), size(size) {}

int UiConstraints::getX() const {
    return UiConstraints::position.x;
}

void UiConstraints::setX(int x) {
    UiConstraints::position.x = x;
}

int UiConstraints::getY() const {
    return UiConstraints::position.y;
}

void UiConstraints::setY(int y) {
    UiConstraints::position.y = y;
}

int UiConstraints::getWidth() const {
    return UiConstraints::size.x;
}

void UiConstraints::setWidth(int width) {
    size.x = width;
}

int UiConstraints::getHeight() const {
    return UiConstraints::size.y;
}

void UiConstraints::setHeight(int height) {
    size.y = height;
}

UiConstraints::UiConstraints() {}

const glm::ivec2 &UiConstraints::getPosition() const {
    return position;
}

void UiConstraints::setPosition(const glm::ivec2 &position) {
    UiConstraints::position = position;
}

const glm::ivec2 &UiConstraints::getSize() const {
    return size;
}

void UiConstraints::setSize(const glm::ivec2 &size) {
    UiConstraints::size = size;
}
