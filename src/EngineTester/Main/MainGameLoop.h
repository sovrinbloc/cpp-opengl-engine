//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H


#include "../../Terrain/Terrain.h"
#include "../../Guis/Text/GUIText.h"

class MainGameLoop {
public:
    static void main();

    static glm::vec3 generateRandomPosition(Terrain *terrain, float yOffset = 0.0f);

    static glm::vec3 generateRandomRotation();

    static float generateRandomScale(float min, float max);

    static void newUiComponent(Loader *loader, GUIText *text);
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
