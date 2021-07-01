//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MODELTEXTURE_H
#define ENGINE_MODELTEXTURE_H
#include "Texture.h"
class ModelTexture {
private:
    Texture *texture;

public:
    ModelTexture(Texture *texture) {
        this->texture = texture;
    }

    Texture *getTexture() {
        return this->texture;
    }
};
#endif //ENGINE_MODELTEXTURE_H
