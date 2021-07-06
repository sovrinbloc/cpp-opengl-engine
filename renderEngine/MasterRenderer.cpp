//
// Created by Joseph Alai on 7/6/21.
//

#include "MasterRenderer.h"
#include "DisplayManager.h"
#include "../toolbox/Maths.h"
#include "RenderStyle.h"

MasterRenderer::MasterRenderer(CameraInput *cameraInput) : shader(new StaticShader()),
                                                           renderer(new EntityRenderer(shader)),
                                                           camera(cameraInput), projectionMatrix(
                Maths::createProjectionMatrix(FOVY, SRC_WIDTH, SRC_HEIGHT, NEAR_PLANE, FAR_PLANE)),
                                                           terrainShader(new TerrainShader()) {
    RenderStyle::enableCulling();
    entities = new std::map<TexturedModel *, std::vector<Entity *>>;
    terrains = new std::vector<Terrain *>;
    terrainRenderer = new TerrainRenderer(terrainShader, this->projectionMatrix);
}

void MasterRenderer::cleanUp() {
    shader->cleanUp();
    terrainShader->cleanUp();
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
}

void MasterRenderer::processTerrain(Terrain *terrain) {
    terrains->push_back(terrain);
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

void MasterRenderer::updatePerspective(float width, float height) {
    SRC_WIDTH = width;
    SRC_HEIGHT = height;
}