//
// Created by Joseph Alai on 2/27/22.
//

#ifndef ENGINE_UIMASTER_H
#define ENGINE_UIMASTER_H


#include "GuiComponent.h"
#include "../RenderEngine/DisplayManager.h"
#include "Rect/RectRenderer.h"
#include "Texture/GuiRenderer.h"
#include "Text/FontRendering/FontRenderer.h"
#include <map>

class UiMaster {
private:
    static UiConstraints *masterConstraints;
    static GuiComponent *masterContainer;
    static std::vector<Container *> renderOrder;

    // try to move everything GUI related into this renderer
    static Loader *loader;
    static GuiRenderer *guiRenderer;
    static RectRenderer *rectRenderer;
    static FontRenderer *fontRenderer;

    static std::map<int, Container *> groupMap;
    static int group;
    static std::map<int, int> tmpGroupMap;


public:
    static const Container *getGroupMap(int group);

    static void setGroup(int group, Container *container);

    static int getCurrentGroup();

    static int newGroup();

    /**
     * Initializes the master container.
     */
    static void
    initialize(Loader *loader, GuiRenderer *guiTextureRenderer, FontRenderer *fontRenderer, RectRenderer *rectRenderer);

    /**
     * @brief applies the constraints to the children. This is to keep the UI as groups.
     *
     * @param component must be the master PARENT component.
     */
    static void applyConstraints(GuiComponent *component);

    /**
     * @brief Gets the constraints of the master UiComponent (the container of all UI components).
     *
     * @return
     */
    static UiConstraints *getMasterConstraints();

    /**
     * @brief Gets the master component. The master component is the container which holds all other
     * Components & Containers.
     *
     * @return
     */
    static GuiComponent *getMasterComponent();

    static void addToLayerQueue(GuiComponent *component);

    static void render();

    static void cleanUp();
};


#endif //ENGINE_UIMASTER_H
