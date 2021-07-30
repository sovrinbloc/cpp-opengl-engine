//
// Created by Joseph Alai on 7/29/21.
//

#ifndef ENGINE_INTERACTIVE_H
#define ENGINE_INTERACTIVE_H

#include "Clickable.h"
#include "Renderable.h"

class Interactive : public Clickable, public Renderable {
public:

    glm::vec3 getRotation() override {}

    float getScale() const override {}

    void setBoundingBox(BoundingBox *box) override {}

    BoundingBox *getBoundingBox() const override {}

    glm::vec3 &getPosition() override {}
};

#endif //ENGINE_INTERACTIVE_H
