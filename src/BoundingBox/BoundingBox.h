//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_BOUNDINGBOX_H
#define ENGINE_BOUNDINGBOX_H
#include "RawBoundingBox.h"
#include "glm/glm.hpp"
#include "../Toolbox/Color.h"

class BoundingBox {
// BoundingBox: A RawBoundingBox + Color

private:
    RawBoundingBox *rawBoundingBox;
    Color color;
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

    /**
     * @brief Returns the Color (Unique ID) of the box
     *
     * @return
     */
    Color getBoxColor() {
        return BoundingBox::color;
    }

    /**
     * @brief Sets the Color (Unique ID) of the bounding box
     * @param color
     */
    void setBoxColor(const Color &color) {
        BoundingBox::color = color;
    }
};
#endif //ENGINE_BOUNDINGBOX_H
