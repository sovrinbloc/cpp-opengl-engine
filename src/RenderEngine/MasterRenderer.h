//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_MASTERRENDERER_H
#define ENGINE_MASTERRENDERER_H

#include <map>
#include <iostream>
#include "../Shaders/StaticShader.h"
#include "../Entities/CameraInput.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SceneRenderer.h"
#include "../Shaders/ModelShader.h"
#include "SceneLoader.h"
#include "../Entities/PlayerCamera.h"
#include "../Skybox/SkyboxRenderer.h"
#include "../Shaders/BoundingBoxShader.h"
#include "BoundingBoxRenderer.h"

static const float FOVY = 45.0f;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000;

class MasterRenderer {
private:
    PlayerCamera *camera;

    StaticShader *shader;
    ModelShader *sceneShader;
    TerrainShader *terrainShader;
    BoundingBoxShader *bShader;

    EntityRenderer *renderer;
    SkyboxRenderer *skyboxRenderer;
    TerrainRenderer *terrainRenderer;
    SceneRenderer *sceneRenderer;
    BoundingBoxRenderer *bRenderer;

    std::map<RawBoundingBox *, std::vector<Entity *>> *boxes;
    std::map<TexturedModel *, std::vector<Entity *>> *entities;
    std::map<Model *, std::vector<Scene *>> *scenes;
    std::vector<Terrain *> *terrains;
    std::vector<Model *> *models;

    glm::mat4 projectionMatrix;
public:
    explicit MasterRenderer(PlayerCamera *cameraInput, Loader *loader);

    void cleanUp();

    /**
     * @brief prepares and clears buffer and screen for each iteration of loop
     */
    void prepare();

    static glm::vec3 skyColor;

    void render(const std::vector<Light *> &sun);

    void processTerrain(Terrain *terrain);

    static glm::mat4 createProjectionMatrix();

    glm::mat4 getProjectionMatrix();

    void processEntity(Entity *entity);

    void processScenes(Scene *scene);

    void processModel(Model *model);

    void processBoundingBox(Entity *entity);

};

#endif //ENGINE_MASTERRENDERER_H
