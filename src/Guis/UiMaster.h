//
// Created by Joseph Alai on 2/27/22.
//

#ifndef ENGINE_UIMASTER_H
#define ENGINE_UIMASTER_H


#include "GuiComponent.h"
#include "../RenderEngine/DisplayManager.h"

class UiMaster {
private:
    static UiConstraints *masterConstraints;
    static GuiComponent *masterContainer;
public:

    /**
     * Initializes the master container.
     */
    static void initialize();

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
};


#endif //ENGINE_UIMASTER_H
