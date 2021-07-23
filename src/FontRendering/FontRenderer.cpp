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

void FontRenderer::render(std::vector<GUIText*> *texts) {
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);

    for (auto t: *texts) {
        float x = t->getPosition().x;
        float y = t->getPosition().y;
        shader->start();

        shader->loadTextColor(t->getColor());
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(t->getFont()->getVaoId());

        // iterate through all characters
        std::string::const_iterator c;
        for (c = t->getText().begin(); c != t->getText().end(); c++)
        {
            Character ch = t->getFontType()->getCharacter(*c);

            float xpos = x + ch.bearing.x * t->getScale();
            float ypos = y - (ch.size.y - ch.bearing.y) * t->getScale();

            float w = ch.size.x * t->getScale();
            float h = ch.size.y * t->getScale();
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
            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, t->getFont()->getVboId());
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * t->getScale(); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        shader->stop();

    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);

}
