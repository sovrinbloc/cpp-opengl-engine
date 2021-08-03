//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_BOUNDINGBOX_H
#define ENGINE_BOUNDINGBOX_H
#include "RawBoundingBox.h"
#include "glm/glm.hpp"
#include "../Toolbox/Color.h"

class BoundingBox {
private:
    RawBoundingBox *rawBoundingBox;
    Color color;
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

    Color getBoxColor() {
        return BoundingBox::color;
    }

    void setColor(const Color &color) {
        BoundingBox::color = color;
    }
};
#endif //ENGINE_BOUNDINGBOX_H
