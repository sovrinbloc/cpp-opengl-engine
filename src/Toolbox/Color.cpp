//
// Created by Joseph Alai on 8/2/21.
//

#include "Color.h"
#include "../Util/CommonHeader.h"

const float Color::kColorBytes = 0xff;

const int Color::kAlphaBytes = 0xff;

const float Color::kAlpha = 0xff / kColorBytes;

Color::Color(float color) : col(ColorRGBA(color)) {}

Color::Color(float colorR, float colorG, float colorB) : col(ColorRGBA (colorR, colorG, colorB, kAlpha)) {}

Color::Color(float colorR, float colorG, float colorB, float colorA) : col(ColorRGBA (colorR, colorG, colorB, colorA)) {}

Color::Color(int inColor) : col(ColorRGBA(inColor, inColor, inColor, kAlphaBytes) / kColorBytes) {}

Color::Color(int colorR, int colorG, int colorB) : col(ColorRGBA(colorR, colorG, colorB, kAlphaBytes) / kColorBytes) {}

Color::Color(int colorR, int colorG, int colorB, int colorA) : col(ColorRGBA (colorR, colorG, colorB, colorA) / kColorBytes) {}

Color::Color(ColorRGBA color) : col(color) {}

Color::Color(ColorRGB color) : col(ColorRGBA(color, kAlpha)) {}

Color::Color() {}

float Color::getR() const {
    return col.r;
}

float Color::getG() const {
    return col.g;
}

float Color::getB() const {
    return col.b;
}

float Color::getA() const  {
    return col.a;
}

ColorRGBA Color::getColorRGBA() {
    return col;
}

ColorRGB Color::getColorRGB() {
    return col;
}

ColorRGBA Color::getColorBytesRGBA() {
    return col * kColorBytes;
}

ColorRGB Color::getColorBytesRGB() {
    return col * kColorBytes;
}

void Color::scale(float s) {
    col *= s;
}

Color Color::duplicate(Color color) {
    auto a = Color(color);
    return a;
}

std::string Color::toString() const {
    PRINT_FIVE("(", col.x, col.y, col.z, "");
    return ("(" + std::to_string(col.x) + ", " + std::to_string(col.y) + ", " + std::to_string(col.z) + ")");
}

void Color::setColor(ColorRGBA color) {
    col = color;
}

void Color::setColor(ColorRGB color) {
    col = ColorRGBA (color, kAlpha);
}

void Color::setColor(ColoriRGBA color) {
    col = static_cast<ColorRGBA >(color) / kColorBytes;
}

void Color::setColor(ColoriRGB color) {
    col = ColorRGBA (color, kAlphaBytes) / kColorBytes;
}
