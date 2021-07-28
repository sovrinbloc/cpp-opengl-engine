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
#include "AssimpEntityRenderer.h"
#include "../Shaders/ModelShader.h"
#include "AssimpEntityLoader.h"
#include "../Entities/PlayerCamera.h"
#include "../Skybox/SkyboxRenderer.h"
#include "../BoundingBox/BoundingBoxShader.h"
#include "../BoundingBox/BoundingBoxRenderer.h"

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
    AssimpEntityRenderer *sceneRenderer;
    BoundingBoxRenderer *bRenderer;

    std::map<RawBoundingBox *, std::vector<Entity *>> *boxes;
    std::map<TexturedModel *, std::vector<Entity *>> *entities;
    std::map<AssimpMesh *, std::vector<AssimpEntity *>> *scenes;
    std::vector<Terrain *> *terrains;
    std::vector<AssimpMesh *> *models;

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

    void processAssimpEntity(AssimpEntity *scene);

    void processModel(AssimpMesh *model);

    void processBoundingBox(Entity *entity);

    void renderScene(std::vector<Entity *> entities, std::vector<AssimpEntity *> aEntities,
                     std::vector<Terrain *> terrains, std::vector<Light *> lights);

    void renderBoundingBoxes(std::vector<Entity*> boxes);

    void render();



};

#endif //ENGINE_MASTERRENDERER_H
