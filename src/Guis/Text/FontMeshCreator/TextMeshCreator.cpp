//
// Created by Joseph Alai on 7/24/21.
//

#include "TextMeshCreator.h"
TextMeshData *TextMeshCreator::createTextMesh(GUIText *text) {
    std::vector<Line > lines = createStructure(text);
    return createQuadVertices(text, &lines);
}

std::vector<Line > TextMeshCreator::createStructure(GUIText *text) {
    char chars[text->getText().length()];
    strcpy(chars, text->getText().c_str());
    std::vector<Line> lines;
    Line currentLine = Line(text->getFontSize(), text->getMaxLineSize());
    Word currentWord = Word(text->getColor(), text->getFontSize());

    for (char c : chars) {
        int ascii = static_cast<int>(static_cast<unsigned char>(c));
        if (ascii == kSpaceAscii) {
            bool added = currentLine.attemptToAddWord(currentWord);
            if (!added) {
                lines.push_back(currentLine);
                currentLine = Line(text->getFontSize(), text->getMaxLineSize());
                auto a = currentLine.attemptToAddWord(currentWord);
            }
            currentWord = Word(text->getColor(), text->getFontSize());
            currentWord.addCharacter(*text->getFontType()->getCharacter(c));
            continue;
        } else if (ascii == kNewLineAscii) {
            lines.push_back(currentLine);
            currentLine = Line(text->getFontSize(), text->getMaxLineSize());
            auto a = currentLine.attemptToAddWord(currentWord);
            currentWord = Word(text->getColor(), text->getFontSize());
            continue;
        }
        Character *character = text->getFontType()->getCharacter(c);
        currentWord.addCharacter(*character);
    }
    completeStructure(&lines, &currentLine, &currentWord, text);
    return lines;
}

void TextMeshCreator::completeStructure(std::vector<Line > *lines, Line *currentLine, Word *currentWord, GUIText *text) {
    bool added = currentLine->attemptToAddWord(*currentWord);
    if (!added) {
        lines->push_back(*currentLine);
        currentLine = new Line(text->getFontSize(), text->getMaxLineSize());
        currentLine->attemptToAddWord(*currentWord);
    }
    lines->push_back(*currentLine);
}

TextMeshData *TextMeshCreator::createQuadVertices(GUIText *text, std::vector<Line > *lines) {
    text->setNumberOfLines(static_cast<int>(lines->size()));
    double cursorX = 0.0f;
    double cursorY = 0.0f;
    auto lineHeight = static_cast<float>(text->getFontType()->getCharacter(*"A")->getSize().y) * text->getFontSize() * ( 1 + (1 * kLineHeight));
    for (auto & line : *lines) {
        if (text->isCentered()) {
            cursorX = (line.getMaxLength() - line.getLineLength()) / 2;
        }

        cursorY += lineHeight + (lineHeight * kLineHeight);

        // this sets the offset only the DELTA cursor x (all inclusive)
        line.setOffset(cursorX, cursorY);

    }
    return new TextMeshData(text->position, *lines, lineHeight);
}