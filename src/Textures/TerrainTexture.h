//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTURE_H
#define ENGINE_TERRAINTEXTURE_H

class TerrainTexture {
private:
    int textureId;
    Material material;
public:
    TerrainTexture(int textureID) : textureId(textureID) {}

    int getTextureID() {
        return this->textureId;
    }
};

#endif //ENGINE_TERRAINTEXTURE_H
