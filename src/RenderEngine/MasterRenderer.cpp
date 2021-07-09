//
// Created by Joseph Alai on 7/6/21.
//

#include "MasterRenderer.h"
#include "DisplayManager.h"
#include "../Toolbox/Maths.h"
#include "RenderStyle.h"
#include "SceneLoader.h"

MasterRenderer::MasterRenderer(CameraInput *cameraInput) : shader(new StaticShader()),
                                                           renderer(new EntityRenderer(shader)),
                                                           camera(cameraInput), projectionMatrix(
                Maths::createProjectionMatrix(FOVY, SRC_WIDTH, SRC_HEIGHT, NEAR_PLANE, FAR_PLANE)),
                                                           terrainShader(new TerrainShader()),
                                                           modelShader(new ModelShader())
                                                           {
    RenderStyle::enableCulling();
    entities = new std::map<TexturedModel *, std::vector<Entity *>>;
    scenes = new std::map<Model *, std::vector<Scene *>>;
    terrains = new std::vector<Terrain *>;
    models = new std::vector<Model *>;
    terrainRenderer = new TerrainRenderer(terrainShader, this->projectionMatrix);
    assimpRenderer = new SceneRenderer(modelShader);
}

void MasterRenderer::cleanUp() {
    shader->cleanUp();
    terrainShader->cleanUp();
    modelShader->cleanUp();
}

/**
 * @brief prepares and clears buffer and screen for each iteration of loop
 */
void MasterRenderer::prepare() {
    // render
    // ------
    glClearColor(.529, .808, .98, 1);
    shader->loadSkyColorVariable(glm::vec3(.529, .808, .98));
    terrainShader->loadSkyColorVariable(glm::vec3(.529, .808, .98));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void MasterRenderer::render(Light *sun) {
    camera->move();

    this->prepare();
    shader->start();
    shader->loadSkyColorVariable(glm::vec3(.529, .808, .98));
    shader->loadLight(sun);
    shader->loadViewPosition(CameraInput::getCamera());
    shader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());
    shader->loadProjectionMatrix(this->createProjectionMatrix());
    renderer->render(entities);

    shader->stop();

    modelShader->start();

    modelShader->loadViewPosition(CameraInput::getCamera());
    modelShader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());
    modelShader->loadProjectionMatrix(this->createProjectionMatrix());
    assimpRenderer->render(scenes);
    modelShader->stop();


    terrainShader->start();
    terrainShader->loadSkyColorVariable(glm::vec3(.529, .808, .98));
    terrainShader->loadLight(sun);
    terrainShader->loadViewPosition(CameraInput::getCamera());
    terrainShader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());
    terrainShader->loadProjectionMatrix(this->createProjectionMatrix());
    terrainRenderer->render(terrains);
    terrains->clear();
    terrainShader->stop();

    entities->clear();
    scenes->clear();
}

void MasterRenderer::processTerrain(Terrain *terrain) {
    terrains->push_back(terrain);
}

void MasterRenderer::processModel(Model *model) {
    models->push_back(model);
}

glm::mat4 MasterRenderer::createProjectionMatrix() {
    // my additions
    return Maths::createProjectionMatrix(camera->getCamera()->Zoom, SRC_WIDTH, SRC_HEIGHT, NEAR_PLANE,
                                         FAR_PLANE);
}

glm::mat4 MasterRenderer::getProjectionMatrix() {
    return this->projectionMatrix;
}

void MasterRenderer::processEntity(Entity *entity) {
    TexturedModel *entityModel = entity->getModel();
    auto batchIterator = entities->find(entityModel);
    if (batchIterator != entities->end()) {
        batchIterator->second.push_back(entity);
    } else {
        std::vector<Entity *> newBatch;
        newBatch.push_back(entity);
        (*entities)[entityModel] = newBatch;
    }
}

void MasterRenderer::processScenes(Scene *scene) {
    Model *model = scene->getModel();
    auto batchIterator = scenes->find(model);
    if (batchIterator != scenes->end()) {
        batchIterator->second.push_back(scene);
    } else {
        std::vector<Scene *> newBatch;
        newBatch.push_back(scene);
        (*scenes)[model] = newBatch;
    }
}

void MasterRenderer::updatePerspective(float width, float height) {
    SRC_WIDTH = width;
    SRC_HEIGHT = height;
}