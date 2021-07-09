//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTURE_H
#define ENGINE_TERRAINTEXTURE_H
class TerrainTexture {
private:
    int textureID;
public:
    TerrainTexture(int textureID) {
        this->textureID = textureID;
    }
    int getTextureID() {
        return this->textureID;
    }
};
#endif //ENGINE_TERRAINTEXTURE_H
