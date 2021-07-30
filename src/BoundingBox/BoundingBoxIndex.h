//
// Created by Joseph Alai on 7/26/21.
//

#ifndef ENGINE_BOUNDINGBOXINDEX_H
#define ENGINE_BOUNDINGBOXINDEX_H

#include "glm/glm.hpp"
#include "../Input/InputMaster.h"
#include "../RenderEngine/DisplayManager.h"
#include "../Interfaces/Interactive.h"
#include <map>

class BoundingBoxIndex {
private:
    static glm::ivec3 colors;

    static int totalColors;

public:
    static glm::vec3 addUniqueColor();

    __attribute__((unused)) static int getIndexByColor(int r, int g, int b);

    static int getIndexByColor(glm::vec3 color);

    glm::vec4 getColorByIndex(int index);

private:
    static glm::vec3 formatColor(glm::vec3 color);
};

#endif //ENGINE_BOUNDINGBOXINDEX_H
