//
// Created by Joseph Alai on 7/22/21.
//

#include "FontRenderer.h"

FontRenderer::FontRenderer() {
    shader = new FontShader();
    shader->start();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(DisplayManager::Width()), 0.0f, static_cast<float>(DisplayManager::Height()));
    shader->loadProjectionMatrix(projection);
    shader->stop();
}

void FontRenderer::cleanUp() {
    shader->cleanUp();
}

// todo: remove this because we will be using the other render method
void FontRenderer::render(std::vector<GUIText*> *texts) {
    prepare();
    for (auto text: *texts) {
        renderText(text);
    }
    endRendering();
}

void FontRenderer::render(std::map<FontType *, std::vector<GUIText *>> *texts) {
    prepare();
    std::map<FontType *, std::vector<GUIText *>>::iterator  it;
    for(it = texts->begin(); it != texts->end(); it++) {
        for (GUIText *text : it->second) {
            renderText(text);
        }
    }
    endRendering();
}

void FontRenderer::renderText(GUIText *text) {
    float x = text->getPosition().x;
    float y = text->getPosition().y;

    shader->loadTextColor(text->getColor());
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(text->getFont()->getVaoId());

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text->getText().begin(); c != text->getText().end(); c++)
    {
        Character *ch = text->getFontType()->getCharacter(*c);

        float xpos = x + ch->getBearing().x * text->getFontSize();
        float ypos = y - (ch->getSize().y - ch->getBearing().y) * text->getFontSize();

        float w = ch->getSize().x * text->getFontSize();
        float h = ch->getSize().y * text->getFontSize();
        // update VBO for each character
        float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
        };

        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch->getTextureId());
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, text->getFont()->getVboId());
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->getAdvance() >> 6) * text->getFontSize(); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FontRenderer::prepare() {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    shader->start();
}

void FontRenderer::endRendering() {
    shader->stop();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}
