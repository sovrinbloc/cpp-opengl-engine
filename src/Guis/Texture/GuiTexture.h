//
// Created by Joseph Alai on 7/18/21.
//

#ifndef ENGINE_GUITEXTURE_H
#define ENGINE_GUITEXTURE_H
#include "glm/glm.hpp"
#include "../GuiComponent.h"

class GuiTexture : public GuiComponent {
private:
    unsigned int textureId;

    glm::vec2 position;

    /**
     * Scale is the percentage out of the height and width of the window
     */
    glm::vec2 scale;
public:
    unsigned int getTexture() ;

    glm::vec2 &getPosition();

    const glm::vec2 &getScale() ;

    GuiTexture(unsigned int textureId, const glm::vec2 &position, const glm::vec2 &scale);
};

#endif //ENGINE_GUITEXTURE_H
