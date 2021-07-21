//
// Created by Joseph Alai on 7/6/21.
//

#include "ModelTexture.h"

#include <utility>
#include "../Toolbox/FileSystem.h"

ModelTexture::ModelTexture(std::string filename, ImageType type, Material materials) :
        material(materials) ,TextureLoader(FileSystem::Texture(std::move(filename)), type) {}

int ModelTexture::getNumberOfRows() const {
    return numberOfRows;
}

void ModelTexture::setNumberOfRows(int numberOfRows) {
    ModelTexture::numberOfRows = numberOfRows;
}
