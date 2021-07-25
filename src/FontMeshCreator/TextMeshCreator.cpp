//
// Created by Joseph Alai on 7/24/21.
//

#include "TextMeshCreator.h"
TextMeshData *TextMeshCreator::createTextMesh(GUIText *text) {
    std::vector<Line *> *lines = createStructure(text);
    return createQuadVertices(text, lines);
}

std::vector<Line *> *TextMeshCreator::createStructure(GUIText *text) {
    char chars[text->getText().length()];
    strcpy(chars, text->getText().c_str());
    auto *lines = new std::vector<Line *>();
    Line *currentLine = new Line(text->getFontSize(), text->getMaxLineSize());
    Word *currentWord = new Word(text->getFontSize());
    for (char c : chars) {
        int ascii = static_cast<int>(static_cast<unsigned char>(c));
        if (ascii == kSpaceAscii) {
            bool added = currentLine->attemptToAddWord(*currentWord);
            if (!added) {
                lines->push_back(currentLine);
                currentLine = new Line(text->getFontSize(), text->getMaxLineSize());
                currentLine->attemptToAddWord(*currentWord);
            }
            currentWord = new Word(text->getFontSize());
            continue;
        } else if (ascii == kNewLineAscii) {
            lines->push_back(currentLine);
            currentLine = new Line(text->getFontSize(), text->getMaxLineSize());
            currentLine->attemptToAddWord(*currentWord);
            currentWord = new Word(text->getFontSize());
            continue;
        }
        Character *character = text->getFontType()->getCharacter(c);
        currentWord->addCharacter(character);
    }
    completeStructure(lines, currentLine, currentWord, text);
    return lines;
}

void TextMeshCreator::completeStructure(std::vector<Line *> *lines, Line *currentLine, Word *currentWord, GUIText *text) {
    bool added = currentLine->attemptToAddWord(*currentWord);
    if (!added) {
        lines->push_back(currentLine);
        currentLine = new Line(text->getFontSize(), text->getMaxLineSize());
        currentLine->attemptToAddWord(*currentWord);
    }
    lines->push_back(currentLine);
}

TextMeshData *TextMeshCreator::createQuadVertices(GUIText *text, std::vector<Line *> *lines) {
    text->setNumberOfLines(static_cast<int>(lines->size()));
    double cursorX = 0.0f;
    double cursorY = 0.0f;
    for (int i = 0; i < lines->size(); i++) {
        if (text->isCentered()) {
            cursorX = ((*lines)[i]->getMaxLength() - (*lines)[i]->getLineLength()) / 2;
        }

        cursorY += kLineHeight * text->getFontSize() * i;
        (*lines)[i]->setOffsetX(text->getPosition().x + cursorX);
        (*lines)[i]->setOffsetY(text->getPosition().y + cursorY);
    }
    return new TextMeshData(lines, kLineHeight * text->getFontSize() * static_cast<double>(lines->size()) +
                                   text->getFontSize() * kLineHeight);
}