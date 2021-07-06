//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_MASTERRENDERER_H
#define ENGINE_MASTERRENDERER_H

#include <map>
#include <iostream>
#include "../shaders/StaticShader.h"
#include "../entities/CameraInput.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

static const float FOVY = 45.0f;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000;

class MasterRenderer {
private:
    StaticShader *shader;
    EntityRenderer *renderer;
    glm::mat4 projectionMatrix;
    CameraInput *camera;

    TerrainRenderer *terrainRenderer;
    TerrainShader *terrainShader;
    std::map<TexturedModel *, std::vector<Entity *>> *entities;
    std::vector<Terrain *> *terrains;

public:
    MasterRenderer(CameraInput *cameraInput);

    void cleanUp();

    /**
     * @brief prepares and clears buffer and screen for each iteration of loop
     */
    void prepare();

    void render(Light *sun);

    void processTerrain(Terrain *terrain);

    glm::mat4 createProjectionMatrix();

    glm::mat4 getProjectionMatrix();

    void processEntity(Entity *entity);

    void updatePerspective(float width, float height);


};

#endif //ENGINE_MASTERRENDERER_H
