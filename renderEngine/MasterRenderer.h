//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_MASTERRENDERER_H
#define ENGINE_MASTERRENDERER_H

#include <map>
#include <iostream>
#include "../shaders/StaticShader.h"
#include "../entities/CameraInput.h"
#include "../entities/Camera.h"
#include "../toolbox/Maths.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"

static const float FOVY = 45.0f;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000;

float ScreenWidth = 800.0f;
float ScreenHeight = 600.0f;

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
    MasterRenderer(CameraInput *cameraInput) : shader(new StaticShader()), renderer(new EntityRenderer(shader)),
                                               camera(cameraInput), projectionMatrix(
                    Maths::createProjectionMatrix(FOVY, ScreenWidth, ScreenHeight, NEAR_PLANE, FAR_PLANE)),
                    terrainShader(new TerrainShader()){
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        entities = new std::map<TexturedModel *, std::vector<Entity *>>;
        terrains  = new std::vector<Terrain *>;
        terrainRenderer = new TerrainRenderer(terrainShader, this->projectionMatrix);
    }

    void cleanUp() {
        shader->cleanUp();
        terrainShader->cleanUp();
    }

    /**
     * @brief prepares and clears buffer and screen for each iteration of loop
     */
    void prepare() {
        // render
        // ------
        glClearColor(.529, .808, .98, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    void render(Light *sun) {
        camera->move();

        this->prepare();
        shader->start();
        shader->loadLight(sun);
        shader->loadViewPosition(CameraInput::getCamera());
        shader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());
        shader->loadProjectionMatrix(this->createProjectionMatrix());

        renderer->render(entities);
        shader->stop();

        terrainShader->start();
        terrainShader->loadLight(sun);
        terrainShader->loadViewPosition(CameraInput::getCamera());
        terrainShader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());
        terrainShader->loadProjectionMatrix(this->createProjectionMatrix());
        terrainRenderer->render(terrains);
        terrains->clear();
        terrainShader->stop();

        entities->clear();
    }

    void processTerrain(Terrain *terrain) {
        terrains->push_back(terrain);
    }

    glm::mat4 createProjectionMatrix() {
        // my additions
        return Maths::createProjectionMatrix(camera->getCamera()->Zoom, ScreenWidth, ScreenHeight, NEAR_PLANE,
                                              FAR_PLANE);
    }

    glm::mat4 getProjectionMatrix() {
        return this->projectionMatrix;
    }

    void processEntity(Entity *entity) {
        TexturedModel *entityModel = entity->getModel();
        auto batchIterator = entities->find(entityModel);
        if (batchIterator != entities->end()) {
            batchIterator->second.push_back(entity);
        } else {
            std::vector<Entity *> newBatch;
            newBatch.push_back(entity);
            (*entities)[entityModel] = newBatch;
        }
        std::vector<Entity *> batch = entities->find(entityModel)->second;
    }

    void updatePerspective(float width, float height) {
        ScreenWidth = width;
        ScreenHeight = height;
    }


};

#endif //ENGINE_MASTERRENDERER_H
