//
// Created by Joseph Alai on 7/23/21.
//

#ifndef ENGINE_GUITEXT_H
#define ENGINE_GUITEXT_H

#include <iostream>
#include "glm/glm.hpp"
#include "TextMeshCreator.h"
#include "FontModel.h"

class GUIText {
private:
    FontModel *font;

    FontType *fontType;

    std::string textString;

    float scale;

    glm::vec2 position;

    glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f);

    float fontSize;

    int textMeshVao;

    int vertexCount;

    float lineMaxSize;

    int numberOfLines;

    bool centerText = false;
public:

    GUIText(FontModel *font, FontType *fontType, const std::string &text, float x, float y, float scale,
            glm::vec3 color);

    glm::vec2 &getPosition();

    FontType *getFontType();

    FontModel *getFont();

    float getScale() const;

    const std::string &getText() const;

    glm::vec3 getColor();

    void setColor(glm::vec3 color);

    GUIText(std::string text, FontType font, float x, float y, float scale, glm::vec3 color);

    void remove();

    int getNumberOfLines();

    int getMesh();

    void setMeshInto(int vao, int verticesCount);

    int getVertexCount();

protected:

    float getFontSize();

    void setNumberOfLines(int number);

    void isCentered();

    float getMaxLineSize();

};


#endif //ENGINE_GUITEXT_H
