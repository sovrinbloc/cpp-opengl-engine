//
// Created by Joseph Alai on 3/9/22.
//

#ifndef ENGINE_MAINGUILOOP_H
#define ENGINE_MAINGUILOOP_H

#include "../../Terrain/Terrain.h"
#include "../../Guis/Text/FontMeshCreator/GUIText.h"

class MainGuiLoop {
public:
    static void main();

    static glm::vec3 generateRandomPosition(Terrain *terrain, float yOffset = 0.0f);

    static glm::vec3 generateRandomRotation();

    static float generateRandomScale(float min, float max);
};


#endif //ENGINE_MAINGUILOOP_H
