//
// Created by Joseph Alai on 2/26/22.
//

#ifndef ENGINE_GUICOMPONENT_H
#define ENGINE_GUICOMPONENT_H

#include <iostream>
#include "UiContainer.h"

class GuiComponent : public UiContainer {
public:
    explicit GuiComponent(GuiType type) : UiContainer(type) {}

    GuiComponent(GuiType type, UiConstraints *constraints) : UiContainer(type) {
        this->setConstraints(constraints);
    }

    void show() override;

    bool isDisplayed() override;

    void hide() override;

    bool isClicked() override;

    bool isMouseOver() override;

    bool isMouseOverChild() override;
};

#endif //ENGINE_GUICOMPONENT_H
