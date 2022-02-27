//
// Created by Joseph Alai on 2/25/22.
//

#include "UiConstraints.h"

UiConstraints::UiConstraints(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

int UiConstraints::getX() const {
    return x;
}

void UiConstraints::setX(int x) {
    UiConstraints::x = x;
}

int UiConstraints::getY() const {
    return y;
}

void UiConstraints::setY(int y) {
    UiConstraints::y = y;
}

int UiConstraints::getWidth() const {
    return width;
}

void UiConstraints::setWidth(int width) {
    UiConstraints::width = width;
}

int UiConstraints::getHeight() const {
    return height;
}

void UiConstraints::setHeight(int height) {
    UiConstraints::height = height;
}

UiConstraints::UiConstraints() {}
