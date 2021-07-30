//
// Created by Joseph Alai on 7/26/21.
//

#include "BoundingBoxIndex.h"

glm::ivec3 BoundingBoxIndex::colors;

int BoundingBoxIndex::totalColors;

glm::vec3 BoundingBoxIndex::addUniqueColor() {
    totalColors++;
    colors.b = totalColors % 256;
    colors.g = ((totalColors - colors.b) / 256) % 256;
    colors.r = ((totalColors - colors.b) / 256 ^ 2) - colors.g / 256;
    return glm::vec3(colors) / 255.0f;
}

__attribute__((unused)) int BoundingBoxIndex::getIndexByColor(int r, int g, int b) {
    return (r) | (g << 8) | (b << 16);
}

int BoundingBoxIndex::getIndexByColor(glm::vec3 color) {
    glm::ivec3 iColor = static_cast<glm::ivec3>(formatColor(color));
    auto index = (iColor.r) | (iColor.g << 8) | (iColor.b << 16);
    return index == -16777471 ? -1 : index;
}

glm::vec4 BoundingBoxIndex::getColorByIndex(int index) {
    int r = index & 0xFF;
    int g = (index >> 8) & 0xFF;
    int b = (index >> 16) & 0xFF;

    return glm::vec4(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, 1.0f);
}

glm::vec3 BoundingBoxIndex::formatColor(glm::vec3 color) {
    if ((color.x < 1 && color.x > 0) || (color.y < 1 && color.y > 0) || (color.z < 1 && color.z > 0)) {
        return color * 255.0f;
    }
    return color;
}
