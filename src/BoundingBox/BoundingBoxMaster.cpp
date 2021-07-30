//
// Created by Joseph Alai on 7/26/21.
//

#include "BoundingBoxMaster.h"

glm::ivec3 BoundingBoxMaster::colors;
int BoundingBoxMaster::totalColors;
glm::vec3 BoundingBoxMaster::getColor() {
    totalColors++;
    colors.b = totalColors % 256;
    colors.g = ((totalColors-colors.b)/256) % 256;
    colors.r = ((totalColors-colors.b)/256^2) - colors.g/256;
    printf("%d, %d, %d, totalColors: %d\n", colors.x, colors.y, colors.z, totalColors);
    return glm::vec3(colors) / 255.0f;
}

int BoundingBoxMaster::getIndexByColor(int r, int g, int b) {
    return (r)|(g<<8)|(b<<16);
}

int BoundingBoxMaster::getIndexByColor(glm::vec3 color) {
    glm::ivec3 iColor = static_cast<glm::ivec3>(color * 255.0f);
    return (iColor.r)|(iColor.g<<8)|(iColor.b<<16);
}

glm::vec4 BoundingBoxMaster::getColorByIndex(int index)
{
    int r = index&0xFF;
    int g = (index>>8)&0xFF;
    int b = (index>>16)&0xFF;

    return glm::vec4(float(r)/255.0f, float(g)/255.0f, float(b)/255.0f, 1.0f);
}