//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_BOUNDINGBOX_H
#define ENGINE_BOUNDINGBOX_H
#include "RawBoundingBox.h"
#include "glm/glm.hpp"

class BoundingBox {
private:
    RawBoundingBox *rawBoundingBox;
    glm::vec3 color;
public:
public:

    /**
     * @brief BoundingBox stores the RawBoundingBox [the VaoId] (from loaded mesh details),
     *        the glm::vec3 color, so that it can be used to track clicks on the bounding
     *        boxes.
     *
     * @param rawBoundingBox
     * @param color
     */
    BoundingBox(RawBoundingBox *rawBoundingBox, glm::vec3 color) : rawBoundingBox(rawBoundingBox), color(color) {}

    RawBoundingBox *getRawBoundingBox() {
        return BoundingBox::rawBoundingBox;
    }

    glm::vec3 getBoxColor() {
        return BoundingBox::color;
    }

    void setColor(const glm::vec3 &color) {
        BoundingBox::color = color;
    }
};
#endif //ENGINE_BOUNDINGBOX_H
