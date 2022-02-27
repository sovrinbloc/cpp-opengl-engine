//
// Created by Joseph Alai on 2/25/22.
//

#ifndef ENGINE_UICONSTRAINTS_H
#define ENGINE_UICONSTRAINTS_H


class UiConstraints {

private:
    int x;
    int y;
    int width;
    int height;

public:
    UiConstraints();

    UiConstraints(int x, int y, int width, int height);

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
