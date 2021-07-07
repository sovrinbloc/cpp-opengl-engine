//
// Created by Joseph Alai on 7/6/21.
//

#include "ModelTexture.h"

ModelTexture::ModelTexture(std::string filename, ImageType type,
                           Material materials
) :
        TextureLoader(filename, type) {
    this->material = materials;
}