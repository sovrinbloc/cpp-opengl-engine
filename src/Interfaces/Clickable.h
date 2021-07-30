//
// Created by Joseph Alai on 7/29/21.
//

#ifndef ENGINE_CLICKABLE_H
#define ENGINE_CLICKABLE_H
#include "../BoundingBox/BoundingBox.h"
class Clickable {
public:
    virtual BoundingBox *getBoundingBox() const{}

    virtual void setBoundingBox(BoundingBox *box){}
};
#endif //ENGINE_CLICKABLE_H
