//
// Created by Joseph Alai on 7/22/21.
//

#ifndef ENGINE_TEXTMESHDATA_H
#define ENGINE_TEXTMESHDATA_H

#include <iostream>
#include "glm/glm.hpp"
#include <map>
#include "Character.h"
#include "Line.h"
#include <utility>

class FontType {
public:
    explicit FontType(std::map<char, Character *> *characters);

    Character *getCharacter(char c);

private:
    std::string fontName;

    std::map<char, Character *> *characters;
};

class TextMeshData {

public:

    TextMeshData(glm::vec2 startPos, std::vector<Line> lines, double lineHeight);

    static FontType loadFont(const std::string &location, int size);

    std::vector<Line > getLines() const;

    double getLineHeight() const;

    glm::vec2 getStartPos() const;

    void setStartPos(glm::vec2 position);

private:

    std::vector<Line > lines;

    double lineHeight;

    glm::vec2 startPosition;

};


#endif //ENGINE_TEXTMESHDATA_H
