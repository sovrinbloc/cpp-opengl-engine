//
// Created by Joseph Alai on 2/25/22.
//
#include "GuiComponent.h"

void GuiComponent::show() {
    visible = true;
}

bool GuiComponent::isDisplayed()  {
    return visible;
}

void GuiComponent::hide()  {
    visible = false;
}

bool GuiComponent::isClicked()  {
    return clicked;
}

bool GuiComponent::isMouseOver()  {
    return mouseOver;
}

void GuiComponent::setConstraints(UiConstraints constraints)  {
    this->constraints = constraints;
}

bool GuiComponent::isMouseOverChild()  {
    return false;
}