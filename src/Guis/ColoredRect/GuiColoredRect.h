//
// Created by Joseph Alai on 2/26/22.
//

#ifndef ENGINE_GUICOLOREDRECT_H
#define ENGINE_GUICOLOREDRECT_H
#include "glm/glm.hpp"
#include "../../Toolbox/Color.h"
#include "../GuiComponent.h"


class GuiColoredRect : public GuiComponent {
private:
    Color color;

    glm::vec2 position;

    /**
     * Scale is the percentage out of the height and width of the window
     */
    glm::vec2 scale;
public:
    Color getColor() ;

    glm::vec2 &getPosition();

    const glm::vec2 &getScale() ;

    GuiColoredRect(Color color, const glm::vec2 &position, const glm::vec2 &scale);
};


#endif //ENGINE_GUICOLOREDRECT_H
