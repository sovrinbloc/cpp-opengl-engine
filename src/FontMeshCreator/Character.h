//
// Created by Joseph Alai on 7/23/21.
//

#ifndef ENGINE_CHARACTER_H
#define ENGINE_CHARACTER_H
#include "glm/glm.hpp"
#include <iostream>
class Character {
private:
    // ID handle of the glyph texture
    glm::ivec2 size;       // size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
    unsigned int textureId;
public:
    
    Character(
            unsigned int textureId,  // ID handle of the glyph texture
            glm::ivec2 size,       // size of glyph
            glm::ivec2 bearing,    // Offset from baseline to left/top of glyph
            unsigned int advance    // Offset to advance to next glyph
            ) {
        this->textureId = textureId;
        this->size = size;
        this->bearing = bearing;
        this->advance = advance;
    }

    unsigned int getTextureId() const {
        return textureId;
    }

    const glm::ivec2 &getSize() const {
        return size;
    }

    const glm::ivec2 &getBearing() const {
        return bearing;
    }

    unsigned int getAdvance() const {
        return advance;
    }
};
#endif //ENGINE_CHARACTER_H
