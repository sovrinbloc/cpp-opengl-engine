//
// Created by Joseph Alai on 7/23/21.
//

#include "GUIText.h"
#include "../FontRendering/TextMaster.h"

GUIText::GUIText(const std::string &textString, float fontSize, FontModel *font, FontType *fontType, glm::vec2(position),
                 glm::vec3 color, float maxLineLength = 1.0f, bool centered = false) {
    this->textString = textString;
    this->font = font;
    this->fontType = fontType;
    this->position = position;
    this->fontSize = fontSize;
    this->color = color;
    this->lineMaxLength = maxLineLength;
    this->centerText = centered;
    TextMaster::loadText(this);
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

float GUIText::getFontSize() const {
    return this->fontSize;
}

glm::vec3 GUIText::getColor() {
    return this->color;
}

void GUIText::setColor(glm::vec3 color) {
    this->color = color;
}

void GUIText::remove() {
    TextMaster::remove(this);
}

int GUIText::getNumberOfLines() const {
    return numberOfLines;
}

float GUIText::getMaxLineSize() const {
    return this->lineMaxLength;
}

void GUIText::setNumberOfLines(int number) {
    this->numberOfLines = number;
}

bool GUIText::isCentered() const {
    return centerText;
}
