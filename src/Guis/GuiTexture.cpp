//
// Created by Joseph Alai on 7/18/21.
//

#include "GuiTexture.h"

GuiTexture::GuiTexture(int texture, const glm::vec2 & position, const glm::vec2 & scale):texture(texture),position(position),scale(scale){}

int GuiTexture::getTexture() const {
    return texture;
}

const glm::vec2 &GuiTexture::getPosition() const {
    return position;
}

const glm::vec2 &GuiTexture::getScale() const {
    return scale;
}