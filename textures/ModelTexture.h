//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MODELTEXTURE_H
#define ENGINE_MODELTEXTURE_H
#include "Texture.h"
class ModelTexture : public Texture{
public:
    ModelTexture(std::string filename, ImageType type) : Texture(filename, type) {}
};
#endif //ENGINE_MODELTEXTURE_H
