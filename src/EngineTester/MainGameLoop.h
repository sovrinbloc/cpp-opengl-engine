//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H


#include "../Terrain/Terrain.h"

class MainGameLoop {
public:
    static void main();

    static glm::vec3 generateRandomPosition(Terrain *terrain);

    static glm::vec3 generateRandomRotation();

    static float generateRandomScale(float min, float max);
};
#endif //CRAFTPROJ_MAINGAMELOOP_H
