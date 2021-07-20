//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTUREPACK_H
#define ENGINE_TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"

class TerrainTexturePack {
private:
    TerrainTexture *backgroundTexture;
    TerrainTexture *rTexture;
    TerrainTexture *gTexture;
    TerrainTexture *bTexture;
    Material material;

public:
    TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture,
                       TerrainTexture *gTexture, TerrainTexture *bTexture, Material material = Material{
            .shininess = 1.0f,
            .reflectivity = 0.5f
    }) : backgroundTexture(
            backgroundTexture), rTexture(rTexture), gTexture(gTexture), bTexture(bTexture), material(material) {}

    TerrainTexture *getBackgroundTexture() {
        return backgroundTexture;
    }

    TerrainTexture *getRTexture() {
        return rTexture;
    }

    TerrainTexture *getGTexture() {
        return gTexture;
    }

    TerrainTexture *getBTexture() {
        return bTexture;
    }

    Material getMaterial() {
        return this->material;
    }
};

#endif //ENGINE_TERRAINTEXTUREPACK_H
