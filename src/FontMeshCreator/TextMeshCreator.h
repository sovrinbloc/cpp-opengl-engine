//
// Created by Joseph Alai on 7/22/21.
//

#ifndef ENGINE_TEXTMESHCREATOR_H
#define ENGINE_TEXTMESHCREATOR_H

#include <iostream>
#include "glm/glm.hpp"
#include <map>
#include "Character.h"

class FontType {
public:
    FontType(std::string fontName, std::map<char, Character> Characters);
    Character getCharacter(char c);
private:
    std::string fontName;
    std::map<char, Character> Characters;
};

class TextMeshCreator {
public:
    static FontType loadFont(const std::string& fontName, const std::string& location);
};


#endif //ENGINE_TEXTMESHCREATOR_H
