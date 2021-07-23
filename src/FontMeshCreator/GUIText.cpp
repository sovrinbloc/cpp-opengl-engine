//
// Created by Joseph Alai on 7/23/21.
//

#include "GUIText.h"

#include <utility>

GUIText::GUIText(FontModel *font, FontType *fontType, const std::string& text, float x, float y, float scale,
                 glm::vec3 color) {
    this->textString = text;
    this->font = font;
    this->fontType = fontType;
    this->position = glm::vec2(x, y);
    this->scale = scale;
    this->color = color;
}

const std::string &GUIText::getText() const {
    return this->textString;
}

FontModel *GUIText::getFont() {
    return this->font;
}

FontType *GUIText::getFontType() {
    return this->fontType;
}

glm::vec2 &GUIText::getPosition() {
    return this->position;
}

float GUIText::getScale() const {
    return this->scale;
}

glm::vec3 GUIText::getColor() {
    return this->color;
}

void GUIText::setColor(glm::vec3 color) {
    this->color = color;
}
