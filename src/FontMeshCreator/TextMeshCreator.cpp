//
// Created by Joseph Alai on 7/22/21.
//

#include "TextMeshCreator.h"
#include "../Util/FileSystem.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <utility>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include "GLFW/glfw3.h"


FontType::FontType(std::string fontName, std::map<char, Character> C)
        : fontName(std::move(fontName)), Characters(std::move(C)) {

}

Character FontType::getCharacter(char c) {
    return Characters.at(c);
}

FontType TextMeshCreator::loadFont(const std::string &fontName, const std::string &location) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, FileSystem::Font(location).c_str(), 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
        std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    std::map<char, Character> FontCharacters;
    for (unsigned char c = 0; c < 128; c++) {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
                .textureId = texture,
                .size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                .bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                .advance = static_cast<unsigned int>(face->glyph->advance.x)
        };
        FontCharacters.insert(std::pair<char, Character>(c, character));
//        printf("character at %f, %f, %d, %d, %d, %d\n", static_cast<float>(character.size.x), static_cast<float>(character.size.y), character.bearing.x, character.bearing.y, character.advance, character.textureId);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return FontType(fontName, FontCharacters);
}
