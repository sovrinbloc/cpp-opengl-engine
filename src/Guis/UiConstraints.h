//
// Created by Joseph Alai on 2/25/22.
//

#ifndef ENGINE_UICONSTRAINTS_H
#define ENGINE_UICONSTRAINTS_H


#include "glm/glm.hpp"

class UiConstraints {

private:
    glm::vec2 position = glm::vec2(0.0f);

    // todo: Should a constrained size smaller than the component itself either truncate or shrink the component?
    glm::vec2 size = glm::vec2(0.0f);
public:
    UiConstraints();

    UiConstraints(float x, float y, float width, float height);

    UiConstraints(glm::vec2 position, glm::vec2 size);

    const glm::vec2 &getPosition() const;

    void setPosition(const glm::vec2 &position);

    const glm::vec2 &getSize() const;

    void setSize(const glm::vec2 &size);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);
};


#endif //ENGINE_UICONSTRAINTS_H
