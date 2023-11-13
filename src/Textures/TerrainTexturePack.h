//
// Created by Joseph Alai on 7/9/21.
//

#ifndef ENGINE_TERRAINTEXTUREPACK_H
#define ENGINE_TERRAINTEXTUREPACK_H

#include "TerrainTexture.h"

/**
 * TerrainTexturePack stores the TerrainTextures of all the different
 * Terrain Textures to be blended. Each TerrainTexture has one textureId
 * which will later be bound.
 */
class TerrainTexturePack {
private:
    TerrainTexture *backgroundTexture;
    TerrainTexture *rTexture;
    TerrainTexture *gTexture;
    TerrainTexture *bTexture;
    Material material{};

public:
    /**
     * @brief TerrainTexturePack stores the previously loaded Textures and material
     *         to be able to blend later.
     * @param backgroundTexture
     * @param rTexture
     * @param gTexture
     * @param bTexture
     * @param material
     */
    TerrainTexturePack(TerrainTexture *backgroundTexture, TerrainTexture *rTexture,
                       TerrainTexture *gTexture, TerrainTexture *bTexture, Material material = Material{
            .shininess = 2.0f,
            .reflectivity = 2.0f
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
