//
// Created by Joseph Alai on 7/23/21.
//

#ifndef ENGINE_WORD_H
#define ENGINE_WORD_H


#include "Character.h"
#include <iostream>
#include <vector>

class Word {
private:
    std::vector<Character> characters;

    double width = 0;

    double fontSize;

    glm::vec3 color;

protected:

public:

    /**
     * @return The list of characters in the word.
     */
    std::vector<Character> getCharacters();

    /**
     * Adds a character to the end of the current word and increases the screen-space width of the word.
     * @param character - the character to be added.
     */
    void addCharacter(Character character);
    /**
     * Create a new empty word.
     * @param fontSize - the font size of the text which this word is in.
     */
    explicit Word(glm::vec3 color, double fontSize);

    /**
     * @return The width of the word in terms of screen size.
     */
    double getWordWidth();

    const glm::vec3 &getColor() const;
};


#endif //ENGINE_WORD_H
