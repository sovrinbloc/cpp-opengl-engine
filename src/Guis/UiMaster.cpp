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


void UiMaster::applyConstraints() {
    applyConstraints(masterContainer);
}

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

    // traverse through children
//    for (Container *c : component->SortChildrenByLayer(true)) {
    for (Container *c : component->getChildren()) {
        // get adjustments made by parent. (initialization)
        glm::vec2 adjustments(0.0f);

        // add the child's constraints to the parent's constraints (relativity)
        if (component->getConstraints() != nullptr) {
            glm::vec2 parentPosition = component->getConstraints()->getPosition();
            if (component->getConstraints()->hasAdjustedPosition()) {
                parentPosition = component->getConstraints()->getAdjustedPosition();
            }
            adjustments += parentPosition;
            std::cout << adjustments.x << ", " << adjustments.y << " is the new `adjustments` variable." << std::endl;
        }

        // check to see which type the component is: and perform the action based on that.
        switch (c->getType()) {
            case Container::IMAGE: {
                auto *p = dynamic_cast<GuiTexture *>(c);

                // adds parent adjustment, plus their original position.
                const glm::vec2 &totalAdjustment = adjustments + p->getPosition();
                p->getConstraints()->setPositionAdjustment(totalAdjustment);
                break;
            }
            case Container::TEXT: {
                auto *p = dynamic_cast<GUIText *>(c);
                const glm::vec2 &totalAdjustment = adjustments * glm::vec2(DisplayManager::Width()) + p->getPosition();
                p->getConstraints()->setPositionAdjustment(totalAdjustment);
                break;
            }
            case Container::COLORED_BOX: {
                auto *p = dynamic_cast<GuiRect *>(c);
                const glm::vec2 &totalAdjustment = adjustments + p->getPosition();

                p->getConstraints()->setPositionAdjustment(totalAdjustment);
                break;
            }
            case Container::CONTAINER: {
                auto *p = dynamic_cast<GuiComponent *>(c);
                p->setConstraints(new UiConstraints(adjustments, min(p->getConstraints()->getSize(),
                                                                     c->getConstraints()->getSize())));
                break;
            }
        }
        GuiComponent *pComponent = dynamic_cast<GuiComponent *>(c);
        if (pComponent != nullptr) {
            UiMaster::applyConstraints(pComponent);
        }
    }
}

/**
 * @brief This function is to be utilized for children only. Said, the original parent is the master parent, and has
 *        simply master attributes. Anything to be done to the master parent is NOT to be done or called in this fn.
 *
 * @param component
 */
void UiMaster::createRenderQueue(GuiComponent *component) {
    // iterate through children of this component and apply the constraints to them.
    for (Container *c : component->SortChildrenByLayer(true)) {
        UiMaster::addToLayerQueue(dynamic_cast<GuiComponent *>(c));
        UiMaster::createRenderQueue(dynamic_cast<GuiComponent *>(c));
        std::cout << "Added layer to queue" << std::endl;
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
