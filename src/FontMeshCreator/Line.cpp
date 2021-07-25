//
// Created by Joseph Alai on 7/23/21.
//

#include "Line.h"

Line::Line(float fontSize, double maxLength) {
    this->maxLength = maxLength;
    this->fontSize = fontSize;
}

float Line::getFontSize() const {
    return fontSize;
}

/**
 * Attempt to add a word to the line. If the line can fit the word in
 * without reaching the maximum line length then the word is added and the
 * line length increased.
 * 
 * @param word
 *            - the word to try to add.
 * @return {@code true} if the word has successfully been added to the line.
 */

bool Line::attemptToAddWord(Word word) {
    double additionalLength = word.getWordWidth();
    if (currentLineLength + additionalLength <= maxLength) {
        words.push_back(&word);
        currentLineLength += additionalLength;
        return true;
    } else {
        return false;
    }
}

/**
 * @return The max length of the line.
 */
double Line::getMaxLength() const {
    return maxLength;
}

/**
 * @return The current screen-space length of the line.
 */
double Line::getLineLength() const {
    return currentLineLength;
}

/**
 * @return The list of words in the line.
 */
std::vector <Word*> Line::getWords() {
    return words;
}

double Line::getOffsetX() const {
    return offsetX;
}

void Line::setOffsetX(double offsetX) {
    Line::offsetX = offsetX;
}

double Line::getOffsexY() const {
    return offsexY;
}

void Line::setOffsetY(double offsexY) {
    Line::offsexY = offsexY;
}
