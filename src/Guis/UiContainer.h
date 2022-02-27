//
// Created by Joseph Alai on 2/25/22.
//

#ifndef ENGINE_UICONTAINER_H
#define ENGINE_UICONTAINER_H

#include <vector>
#include "UiConstraints.h"
#include "FontMeshCreator/GUIText.h"
#include "Texture/GuiTexture.h"

class UiContainer : Container {
protected:
    UiConstraints constraints;
    UiContainer *parent = nullptr;

    bool visible = true;
    bool clicked = false;
    bool mouseOver = false;
    bool displayed = true;
    bool removeFlag = false;
    bool reloadOnSizeChange = false;
    bool initialized = false;//true after adding to parent and having screen space and alpha calced
    int level = 0;
public:
    UiContainer() : Container(false) {}

    virtual void show() = 0;

    virtual void hide() = 0;

    virtual bool isDisplayed() = 0;

    virtual void setConstraints(UiConstraints constraints) = 0;

    // interactionable should probably be it's own interface:

    virtual bool isMouseOverChild() = 0;

    virtual bool isClicked() = 0;

    virtual bool isMouseOver() = 0;

    // triggerable

};

#endif //ENGINE_UICONTAINER_H
