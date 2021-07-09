//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTURE_H
#define ENGINE_TERRAINTEXTURE_H

class TerrainTexture {
private:
    int textureID;
    Material material;
public:
    TerrainTexture(int textureID) : textureID(textureID) {}

    int getTextureID() {
        return this->textureID;
    }
};

#endif //ENGINE_TERRAINTEXTURE_H
