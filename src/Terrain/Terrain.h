//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAIN_H
#define ENGINE_TERRAIN_H
#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../RenderEngine/Loader.h"
#include "../Textures/TerrainTexturePack.h"
#include "HeightMap.h"

class Terrain {
private:
    const float SIZE = 800;
    const int VERTEX_COUNT = 128;

    float x;
    float z;
    RawModel *model;
    TerrainTexturePack *texturePack;
    TerrainTexture *blendMap;
    Heightmap heightMap;

public:
    float getX() const {
        return x;
    }

    void setX(float x) {
        this->x = x;
    }

    float getZ() const {
        return z;
    }

    void setZ(float z) {
        this->z = z;
    }

    RawModel *getModel() const {
        return model;
    }

    void setModel(RawModel *model) {
        this->model = model;
    }

    TerrainTexturePack *getTexturePack() {
        return this->texturePack;
    }

    TerrainTexture *getBlendMap() {
        return this->blendMap;
    }

    Terrain(int gridX, int gridZ, Loader *loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap, const std::string& heightMap);

private:
    RawModel *generateTerrain(Loader *loader);
};
#endif //ENGINE_TERRAIN_H
