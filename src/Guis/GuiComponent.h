//
// Created by Joseph Alai on 2/26/22.
//

#ifndef ENGINE_GUICOMPONENT_H
#define ENGINE_GUICOMPONENT_H
#include "UiContainer.h"
class GuiComponent : public UiContainer {
public:
    explicit GuiComponent(GuiType type) : UiContainer(type) {}

    void show() override;

    bool isDisplayed() override;

    void hide() override;

    bool isClicked() override;

    bool isMouseOver() override;

    void setConstraints(UiConstraints constraints) override;

    bool isMouseOverChild() override;
};
#endif //ENGINE_GUICOMPONENT_H
