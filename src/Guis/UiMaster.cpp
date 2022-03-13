//
// Created by Joseph Alai on 2/27/22.
//

#include "UiMaster.h"
#include "Texture/GuiTexture.h"
#include "Text/GUIText.h"
#include "Text/Rendering/TextMaster.h"
#include "../Toolbox/Logger/Log.h"
#include "../Util/CommonHeader.h"
#include "Constraints/UiPercentConstraint.h"

GuiComponent *UiMaster::masterContainer;
UiConstraints *UiMaster::masterConstraints;

GuiRenderer *UiMaster::guiRenderer;
RectRenderer *UiMaster::rectRenderer;
FontRenderer *UiMaster::fontRenderer;
Loader *UiMaster::loader;

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
 * @param parentComponent
 */
void UiMaster::applyConstraints(GuiComponent *parentComponent) {
    // iterate through children of this parentComponent and apply the constraints to them.

    // traverse through children
    for (Container *childComponent : parentComponent->SortChildrenByLayer(true)) {

        childComponent->constraints->parentPosition =
                parentComponent->constraints->parentPosition + parentComponent->constraints->position;

        // check to see which type the parentComponent is: and perform the action based on that.
        switch (childComponent->getType()) {
            case Container::IMAGE: {
                auto *p = dynamic_cast<GuiTexture *>(childComponent);
                p->constraints->parentPosition =
                        parentComponent->constraints->position + parentComponent->constraints->parentPosition;

                break;
            }
            case Container::TEXT: {
                auto *p = dynamic_cast<GUIText *>(childComponent);
                p->constraints->parentPosition =
                        parentComponent->constraints->position + parentComponent->constraints->parentPosition;

                break;
            }
            case Container::COLORED_BOX: {
                auto *p = dynamic_cast<GuiRect *>(childComponent);
                p->constraints->parentPosition =
                        parentComponent->constraints->position + parentComponent->constraints->parentPosition;

                break;
            }
            case Container::CONTAINER: {
                auto *p = dynamic_cast<GuiComponent *>(childComponent);
                p->constraints->parentPosition =
                        parentComponent->constraints->position + parentComponent->constraints->parentPosition;

                break;
            }
        }

        auto *pComponent = dynamic_cast<GuiComponent *>(childComponent);
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
    masterConstraints = new UiConstraints(new UiPercentConstraint(XAxis, 0.0f), new UiPercentConstraint(YAxis, 0.0f),
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

// fixme: some components do not show up on some renders (randomly or so it seems).
// todo: Should we proceed to only not render if it is visible, in here? I think so. Added: 3/3/2022
/**
 * This is what was just added, thus we should test this by removing the render of the other components.
 */
void UiMaster::render() {
    int i = 0;
    for (Container *c: renderOrder) {
        {
            if (c->isHidden()) {
                std::cout << c->getName() << " is hidden" << std::endl;
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
