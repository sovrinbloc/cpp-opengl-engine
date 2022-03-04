//
// Created by Joseph Alai on 2/27/22.
//

#include "UiMaster.h"
#include "Texture/GuiTexture.h"
#include "Text/FontMeshCreator/GUIText.h"
#include "Text/FontRendering/TextMaster.h"

GuiComponent *UiMaster::masterContainer;
UiConstraints *UiMaster::masterConstraints;

GuiRenderer *UiMaster::guiRenderer;
RectRenderer *UiMaster::rectRenderer;
FontRenderer *UiMaster::fontRenderer;
Loader *UiMaster::loader;

// todo: implement the groups properly and make it each layer can be identified from each other,
//  including each child component can be differentiated in layer from it's parents with group and child...
//  example: instead of parent having layer = 1, and child having layers 1, 2, and 3, you would have...
//  parent having 1.1, and child having 2.1, 2.2, 2.3
std::map<int, Container *> UiMaster::groupMap = std::map<int, Container *>();
std::map<int, int> UiMaster::tmpGroupMap = std::map<int, int>();
int UiMaster::group = 0;

/**
 * @brief This function is to be utilized for children only. Said, the original parent is the master parent, and has
 *        simply master attributes. Anything to be done to the master parent is NOT to be done or called in this fn.
 *
 * @param component
 */
void UiMaster::applyConstraints(GuiComponent *component) {
    // iterate through children of this component and apply the constraints to them.
    std::cout << "Iterating through the component named: " << component->getName() << std::endl;
    if (component->getParent() != nullptr) {
        std::cout << "There is a parent named: " << component->getParent()->getName() << std::endl;
    }
    for (Container *c : component->SortChildrenByLayer(true)) {
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
                case Container::COLORED_BOX: {
                    auto *p = dynamic_cast<GuiRect *>(c);
                    if (c->getConstraints() == nullptr) {
                        std::cout << "contraints null on colored box";
                    }
                    p->getPosition() += c->getConstraints()->getPosition();
                    break;
                }
                case Container::CONTAINER: {
                    auto *p = dynamic_cast<GuiComponent *>(c);
                    glm::vec2 currentPosition = p->getConstraints()->getPosition();
                    glm::vec2 addPosition = c->getConstraints()->getPosition();
                    auto newPosition = currentPosition += addPosition;
                    p->setConstraints(new UiConstraints(newPosition, min(p->getConstraints()->getSize(),
                                                                         c->getConstraints()->getSize())));
                    break;
                }
            }
            if (!c->isSterile()) {
                UiMaster::applyConstraints(dynamic_cast<GuiComponent *>(c));

                // adds this ordered child to the render queue.
                UiMaster::addToLayerQueue(dynamic_cast<GuiComponent *>(c));
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

void UiMaster::initialize(Loader *loader, GuiRenderer *guiTextureRenderer, FontRenderer *fontRenderer,
                          RectRenderer *rectRenderer) {
    masterConstraints = new UiConstraints(0.0f, -0.0f,
                                          static_cast<float>(DisplayManager::Width()),
                                          static_cast<float>(DisplayManager::Height()));
    masterContainer = new GuiComponent(Container::CONTAINER, masterConstraints);
    masterContainer->setName("master");
    // add the master container as the first to be rendered
    renderOrder.push_back(masterContainer);

    // this loader is used for the gui renderers
    UiMaster::loader = loader;
    UiMaster::guiRenderer = guiTextureRenderer;
    UiMaster::rectRenderer = rectRenderer;
    UiMaster::fontRenderer = fontRenderer;
}

std::vector<Container *> UiMaster::renderOrder = std::vector<Container *>();

/**
 * Adds this layer to the layer queue because it is in order.
 * @param component
 */
void UiMaster::addToLayerQueue(GuiComponent *component) {
    renderOrder.push_back(component);
}

// todo: Should we proceed to only not render if it is visible, in here? I think so. Added: 3/3/2022
/**
 * This is what was just added, thus we should test this by removing the render of the other components.
 */
void UiMaster::render() {
    for (Container *c: renderOrder) {
        {
            if (c->isHidden()) {
                continue;
            }

            // check to see which type the component is: and perform the action based on that.
            switch (c->getType()) {
                case Container::IMAGE: {
                    auto *p = dynamic_cast<GuiTexture *>(c);
                    guiRenderer->render(p);
                    break;
                }
                case Container::TEXT: {
                    auto *p = dynamic_cast<GUIText *>(c);
                    fontRenderer->render(p);
                    break;
                }
                case Container::COLORED_BOX: {
                    auto *p = dynamic_cast<GuiRect *>(c);
                    rectRenderer->render(p);
                    break;
                }
                case Container::CONTAINER: {
                    auto *p = dynamic_cast<GuiComponent *>(c);
                    break;
                }
            }
        }
    }
}

int UiMaster::newGroup() {
    group += 1;
    return group;
}

int UiMaster::getCurrentGroup() {
    return group;
}

void UiMaster::setGroup(int group, Container *container) {
    groupMap[group] = container;
}

const Container *UiMaster::getGroupMap(int group) {
    return groupMap[group];
}
