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
#include "../Toolbox/Color.h"

class BoundingBoxIndex {
private:
    static glm::ivec3 colors;

    static int totalColors;

public:
    static ColorRGB genUniqueId();

    __attribute__((unused)) static int getIndexByColor(int r, int g, int b);

    static int getIndexByColor(Color color);

    ColorRGBA getColorByIndex(int index);

private:
    static glm::vec3 formatColor(glm::vec3 color);
};

#endif //ENGINE_BOUNDINGBOXINDEX_H
