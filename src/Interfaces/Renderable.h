//
// Created by Joseph Alai on 7/29/21.
//

#ifndef ENGINE_RENDERABLE_H
#define ENGINE_RENDERABLE_H
#include "glm/glm.hpp"
class Renderable {
public:
    virtual glm::vec3 &getPosition(){}
    virtual glm::vec3 getRotation(){}
    virtual float getScale() const{}
};
#endif //ENGINE_RENDERABLE_H
