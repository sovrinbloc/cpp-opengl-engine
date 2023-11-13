//
// Created by Joseph Alai on 7/26/21.
//

#include "BoundingBoxIndex.h"

glm::ivec3 BoundingBoxIndex::colors;

int BoundingBoxIndex::totalColors;
/**
 * Generates a unique ID to assign to a particular object.
 *
 * @return
 */
glm::vec3 BoundingBoxIndex::genUniqueId() {
    totalColors++;
    colors.b = totalColors % 256;
    colors.g = ((totalColors - colors.b) / 256) % 256;
    colors.r = ((totalColors - colors.b) / 256 ^ 2) - colors.g / 256;
    return glm::vec3(colors) / 255.0f;
}

__attribute__((unused)) int BoundingBoxIndex::getIndexByColor(int r, int g, int b) {
    return (r) | (g << 8) | (b << 16);
}

/**
 * Retrieves the ID when inputting the color.
 *
 * @param color
 * @return
 */
int BoundingBoxIndex::getIndexByColor(Color color) {

    glm::ivec3 iColor = static_cast<glm::ivec3>(formatColor(color.getColorRGB()));
    auto index = (iColor.r) | (iColor.g << 8) | (iColor.b << 16);
    if (iColor == glm::ivec3(255)) {
        return -1;
    }
    return index;
}
/**
 * Retrieves the Color by the index
 *
 * @param index
 * @return
 */
glm::vec4 BoundingBoxIndex::getColorByIndex(int index) {
    int r = index & 0xFF;
    int g = (index >> 8) & 0xFF;
    int b = (index >> 16) & 0xFF;

    return glm::vec4(float(r) / 255.0f, float(g) / 255.0f, float(b) / 255.0f, 1.0f);
}

/**
 * Inputs the [0 : 1] color, and returns [0 : 255] color.
 *
 * @param color
 * @return
 */
glm::vec3 BoundingBoxIndex::formatColor(glm::vec3 color) {
    if ((color.x < 1 && color.x > 0) || (color.y < 1 && color.y > 0) || (color.z < 1 && color.z > 0)) {
        return color * 255.0f;
    }
    return color;
}
