//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTURE_H
#define ENGINE_TERRAINTEXTURE_H

/**
 * TerrainTexture simply stores a single Terrain Texture's ID.
 * It is passed in here by a TextureLoader
 */
class TerrainTexture {
private:
    int textureId;
public:
    /**
     * @brief stores the textureId of the image (from textureLoader)
     *        Each texture has it's own unique ID, and they are always
     *        incrementing.
     * @param textureID
     */
    explicit TerrainTexture(int textureID) : textureId(textureID) {}

    int getTextureId() const {
        return this->textureId;
    }
};

#endif //ENGINE_TERRAINTEXTURE_H
