//
// Created by Joseph Alai on 2/26/22.
//

#include "GuiColoredRect.h"

GuiColoredRect::GuiColoredRect(Color color, const glm::vec2 &position, const glm::vec2 &scale) :
        color(color), position(position), scale(scale), GuiComponent(COLORED_BOX) {}

Color GuiColoredRect::getColor() {
    return color;
}

glm::vec2 &GuiColoredRect::getPosition() {
    return position;
}

const glm::vec2 &GuiColoredRect::getScale() {
    return scale;
}