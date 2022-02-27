//
// Created by Joseph Alai on 2/25/22.
//

#ifndef ENGINE_UICONSTRAINTS_H
#define ENGINE_UICONSTRAINTS_H


#include <vec2.hpp>

class UiConstraints {

private:
    glm::ivec2 position = glm::vec2(0.0f);

    // todo: Should a constrained size smaller than the component itself either truncate or shrink the component?
    glm::ivec2 size = glm::vec2(0.0f);
public:
    UiConstraints();

    UiConstraints(int x, int y, int width, int height);

    UiConstraints(glm::ivec2 position, glm::ivec2 size);

    const glm::ivec2 &getPosition() const;

    void setPosition(const glm::ivec2 &position);

    const glm::ivec2 &getSize() const;

    void setSize(const glm::ivec2 &size);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getWidth() const;

    void setWidth(int width);

    int getHeight() const;

    void setHeight(int height);
};


#endif //ENGINE_UICONSTRAINTS_H
