//
// Created by Joseph Alai on 7/18/21.
//

#include "GuiTexture.h"

/**
 * @brief GuiTexture stores the textureId, scale, and the position of the GUI
 * @param textureId
 * @param position
 * @param scale
 */
GuiTexture::GuiTexture(int textureId, const glm::vec2 & position, const glm::vec2 & scale): textureId(textureId), position(position), scale(scale){}

int GuiTexture::getTexture() const {
    return textureId;
}

const glm::vec2 &GuiTexture::getPosition() const {
    return position;
}

const glm::vec2 &GuiTexture::getScale() const {
    return scale;
}