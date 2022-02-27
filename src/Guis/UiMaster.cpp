//
// Created by Joseph Alai on 2/27/22.
//

#include "UiMaster.h"
#include "Texture/GuiTexture.h"
#include "FontMeshCreator/GUIText.h"

GuiComponent *UiMaster::masterContainer;
UiConstraints *UiMaster::masterConstraints;

void UiMaster::applyConstraints(GuiComponent *component) {
    // iterate through children of this component and apply the constraints to them.
    std::cout << "Iterating through the component named: " << component->getName() << std::endl;
    if (component->getParent() != nullptr) {
        std::cout << "There is a parent named: " << component->getParent()->getName() << std::endl;
    }
    for (Container *c: component->getChildrenToAdd()) {
        bool selfModification = c->getConstraints()->getY() != 0 || c->getConstraints()->getX() != 0;
        if (selfModification) {
            glm::vec2 cPos = c->getConstraints()->getPosition();

            if (c->getParent() != nullptr && c->getParent()->getConstraints() != nullptr) {
                cPos += c->getParent()->getConstraints()->getPosition();
            }

            // check to see which type the component is: and perform the action based on that.
            switch (c->getType()) {
                case Container::IMAGE: {
                    auto *p = dynamic_cast<GuiTexture *>(c);
                    p->getPosition() += cPos;
                    break;
                }
                case Container::TEXT: {
                    auto *p = dynamic_cast<GUIText *>(c);
                    p->getPosition() += cPos;
                    break;
                }
                case Container::CONTAINER: {
                    auto *p = dynamic_cast<GuiComponent *>(c);
                    glm::vec2 currentPosition = p->getConstraints()->getPosition();
                    glm::vec2 addPosition = c->getConstraints()->getPosition();
                    auto newPosition = currentPosition += addPosition;
                    p->setConstraints(new UiConstraints(newPosition, min(p->getConstraints()->getSize(), c->getConstraints()->getSize())));
                    break;
                }
                case Container::COLORED_BOX: {
                    auto *p = dynamic_cast<GuiTexture *>(c);
                    p->getPosition() += c->getConstraints()->getPosition();
                    break;
                }
            }
            if (!c->isSterile()) {
                UiMaster::applyConstraints(dynamic_cast<GuiComponent*>(c));
            }
        }
    }
}

GuiComponent *UiMaster::getMasterComponent() {
    return masterContainer;
}

UiConstraints *UiMaster::getMasterConstraints() {
    return masterConstraints;
}

void UiMaster::initialize() {
    masterConstraints = new UiConstraints(0.0f, -0.0f,
                                                                static_cast<float>(DisplayManager::Width()),
                                                                static_cast<float>(DisplayManager::Height()));
    masterContainer = new GuiComponent(Container::CONTAINER, masterConstraints);
    masterContainer->setName("master");
}
