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

public:
    TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture,
                       TerrainTexture *gTexture, TerrainTexture *bTexture) : backgroundTexture(
            backgroundTexture), rTexture(rTexture), gTexture(gTexture), bTexture(bTexture) {}
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
};
#endif //ENGINE_TERRAINTEXTUREPACK_H
