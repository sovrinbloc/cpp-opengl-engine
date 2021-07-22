//
// Created by Joseph Alai on 7/6/21.
//

#include "ModelTexture.h"

#include <utility>
#include "../Util/FileSystem.h"

/**
 * @brief ModelTexture is a child of TextureLoader, which then ultimately
 *        adds more features for loading and returning the textureIds of
 *        images. But in this case, it also allows for texture atlases,
 *        materials, decisions of fake lighting, and transparency.
 *        It loads the image, by type, and materials, and stores the textureId.
 * @param filename std::string
 * @param type (PNG | JPG)
 * @param materials
 */
ModelTexture::ModelTexture(std::string filename, ImageType type, Material materials) :
        material(materials) ,TextureLoader(FileSystem::Texture(std::move(filename)), type) {}

int ModelTexture::getNumberOfRows() const {
    return numberOfRows;
}

void ModelTexture::setNumberOfRows(int numberOfRows) {
    ModelTexture::numberOfRows = numberOfRows;
}
