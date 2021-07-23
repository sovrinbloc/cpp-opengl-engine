//
// Created by Joseph Alai on 7/23/21.
//

#include "Word.h"

Word::Word(double fontSize){
    this->fontSize = fontSize;
}

/**
 * Adds a character to the end of the current word and increases the screen-space width of the word.
 * @param character - the character to be added.
 */
void Word::addCharacter(Character character){
    characters.push_back(character);
    width += character.advance * fontSize;
}

/**
 * @return The list of characters in the word.
 */
std::vector<Character> Word::getCharacters(){
    return characters;
}

/**
 * @return The width of the word in terms of screen size.
 */
double Word::getWordWidth(){
    return width;
}