//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAINRENDERER_H
#define ENGINE_TERRAINRENDERER_H
#include "glm/glm.hpp"
#include "../Shaders/TerrainShader.h"
#include "../Terrain/Terrain.h"

class TerrainRenderer {
private:
    TerrainShader *shader;

public:
    TerrainRenderer(TerrainShader *shader, glm::mat4 projectionMatrix);

    void render(std::vector<Terrain*> *terrains);

private:
    void prepareTerrain(Terrain *terrain);

    void unbindTexturedModel();

    void loadModelMatrix(Terrain *terrain);
};
#endif //ENGINE_TERRAINRENDERER_H
