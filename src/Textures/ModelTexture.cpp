//
// Created by Joseph Alai on 7/6/21.
//

#include "ModelTexture.h"

ModelTexture::ModelTexture(std::string filename, ImageType type,
                           Material materials
) :
        Texture(filename, type) {
    this->material = materials;
}