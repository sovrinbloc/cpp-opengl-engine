//
// Created by Joseph Alai on 8/2/21.
//

#ifndef ENGINE_COLOR_H
#define ENGINE_COLOR_H

#include <iostream>
#include "glm/glm.hpp"

using ColorRGBA = glm::vec4;
using ColorRGB = glm::vec3;
using ColoriRGB = glm::ivec3;
using ColoriRGBA = glm::ivec4;

class Color {
private:
    ColorRGBA col;

    static float const kColorBytes;
    static int const kAlphaBytes;
    static float const kAlpha;

public:
    explicit Color(float color);

    Color();

    Color(float colorR, float colorG, float colorB);

    Color(float colorR, float colorG, float colorB, float colorA);

    explicit Color(int color);

    Color(int colorR, int colorG, int colorB);

    Color(int colorR, int colorG, int colorB, int colorA);

    explicit Color(ColorRGBA color);

    explicit Color(ColorRGB color);

    void setColor(ColorRGBA color);

    void setColor(ColorRGB color);

    void setColor(ColoriRGB color);

    void setColor(ColoriRGBA color);

    float getR() const;

    float getG() const;

    float getB() const;

    float getA() const;

    ColorRGBA getColorRGBA();

    ColorRGB getColorRGB();

    ColorRGBA getColorBytesRGBA();

    ColorRGB getColorBytesRGB();

    void scale(float s);

    Color duplicate(Color color);

    std::string toString() const;

};

#endif //ENGINE_COLOR_H
