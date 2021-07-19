//
// Created by Joseph Alai on 7/6/21.
//

#include "ModelTexture.h"
#include "../Toolbox/FileSystem.h"

ModelTexture::ModelTexture(std::string filename, ImageType type,
                           Material materials
) :
        TextureLoader(FileSystem::Texture(filename), type) {
    this->material = materials;
}

int ModelTexture::getNumberOfRows() const {
    return numberOfRows;
}

void ModelTexture::setNumberOfRows(int numberOfRows) {
    ModelTexture::numberOfRows = numberOfRows;
}
