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
    explicit FontType(std::map<char, Character*> *characters);
    Character *getCharacter(char c);
private:
    std::string fontName;
    std::map<char, Character*> *characters;
};

class TextMeshData {
public:
    static FontType loadFont(const std::string& location, int size);
    TextMeshData(std::vector<Line *> *lines, double lineHeight);
private:
    std::vector<Line*> *lines;
    double lineHeight;
};


#endif //ENGINE_TEXTMESHDATA_H
