//
// Created by Joseph Alai on 7/29/21.
//

#ifndef ENGINE_POSITIONABLE_H
#define ENGINE_POSITIONABLE_H

#include "glm/glm.hpp"

class Positionable {
public:
    virtual glm::vec3 &getPosition() = 0;

    virtual glm::vec3 getRotation() = 0;

    virtual float getScale() const = 0;

    virtual void setPosition(glm::vec3 translate) = 0;

    virtual void increasePosition(glm::vec3 translate) = 0;

    virtual void rotate(glm::vec3 rotate) = 0;

    virtual void setRotation(glm::vec3 rotate) = 0;

    virtual void increaseScale(float scaleSize) = 0;

    virtual void setScale(float scaleSize) = 0;

    virtual void setTransformation(glm::vec3 translate, glm::vec3 rotate, float scalar) = 0;
};

#endif //ENGINE_POSITIONABLE_H
