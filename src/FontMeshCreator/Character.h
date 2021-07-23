//
// Created by Joseph Alai on 7/23/21.
//

#ifndef ENGINE_CHARACTER_H
#define ENGINE_CHARACTER_H
#include "glm/glm.hpp"
struct Character {
    unsigned int textureId;  // ID handle of the glyph texture
    glm::ivec2 size;       // size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};
#endif //ENGINE_CHARACTER_H
