//
// Created by Joseph Alai on 7/18/21.
//

#ifndef ENGINE_GUITEXTURE_H
#define ENGINE_GUITEXTURE_H
#include "glm/glm.hpp"


class GuiTexture {
private:
    int textureId;
    glm::vec2 position;
    glm::vec2 scale;
public:
    int getTexture() const;

    const glm::vec2 &getPosition() const;

    const glm::vec2 &getScale() const;

    GuiTexture(int textureId, const glm::vec2 &position, const glm::vec2 &scale);
};

#endif //ENGINE_GUITEXTURE_H
