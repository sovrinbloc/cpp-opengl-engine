//
// Created by Joseph Alai on 7/6/21.
//

#include "MasterRenderer.h"
#include "DisplayManager.h"
#include "RenderStyle.h"
#include "AssimpEntityLoader.h"
#include "../Util/Colors.h"
#include "../Util/Utils.h"

MasterRenderer::MasterRenderer(PlayerCamera *cameraInput, Loader *loader) : shader(new StaticShader()),
                                                            renderer(new EntityRenderer(shader)),
                                                            camera(cameraInput), projectionMatrix(
                Maths::createProjectionMatrix(FOVY, static_cast<float>(DisplayManager::Width()),
                                              static_cast<float>(DisplayManager::Height()), NEAR_PLANE, FAR_PLANE)),
                                                            terrainShader(new TerrainShader()),
                                                            sceneShader(new AssimpStaticShader()),
                                                            bShader(new BoundingBoxShader()){
    RenderStyle::enableCulling();
    entities = new std::map<TexturedModel *, std::vector<Entity *>>;
    scenes = new std::map<AssimpMesh *, std::vector<AssimpEntity *>>;
    terrains = new std::vector<Terrain *>;
    boxes = new std::map<RawBoundingBox *, std::vector<Interactive *>>;
    terrainRenderer = new TerrainRenderer(terrainShader, this->projectionMatrix);
    sceneRenderer = new AssimpEntityRenderer(sceneShader);
    skyboxRenderer = new SkyboxRenderer(loader, this->projectionMatrix, &skyColor);
    bRenderer = new BoundingBoxRenderer(bShader, this->projectionMatrix);
}

void MasterRenderer::cleanUp() {
    shader->cleanUp();
    terrainShader->cleanUp();
    sceneShader->cleanUp();
    bShader->cleanUp();
}

glm::vec3 MasterRenderer::skyColor = const_cast<glm::vec3 &>(Colors::Skyblue);

/**
 * @brief prepares and clears buffer and screen for each iteration of loop
 */
void MasterRenderer::prepare() {
    // render
    // ------
    glClearColor(skyColor.x, skyColor.y, skyColor.z, 1);
    shader->loadSkyColorVariable(skyColor);
    terrainShader->loadSkyColorVariable(skyColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void MasterRenderer::render(const std::vector<Light *>&suns) {
    this->prepare();

    shader->start();

    shader->loadSkyColorVariable(skyColor);
    shader->loadLight(suns);
    shader->loadViewPosition(camera);
    shader->loadViewMatrix(camera->getViewMatrix());
    shader->loadProjectionMatrix(MasterRenderer::createProjectionMatrix());
    renderer->render(entities);

    entities->clear();
    shader->stop();

    sceneShader->start();
    sceneShader->loadSkyColorVariable(skyColor);
    sceneShader->loadLight(suns);
    sceneShader->loadViewPosition(camera);
    sceneShader->loadViewMatrix(camera->getViewMatrix());
    sceneShader->loadProjectionMatrix(MasterRenderer::createProjectionMatrix());
    sceneRenderer->render(scenes);

    scenes->clear();
    sceneShader->stop();


    terrainShader->start();

    terrainShader->loadSkyColorVariable(skyColor);
    terrainShader->loadLight(suns);
    terrainShader->loadViewPosition(camera);
    terrainShader->loadViewMatrix(camera->getViewMatrix());
    terrainShader->loadProjectionMatrix(MasterRenderer::createProjectionMatrix());
    terrainRenderer->render(terrains);

    terrains->clear();
    terrainShader->stop();
    skyboxRenderer->render(camera);

}

void MasterRenderer::processTerrain(Terrain *terrain) {
    terrains->push_back(terrain);
}

glm::mat4 MasterRenderer::createProjectionMatrix() {
    // my additions
    return Maths::createProjectionMatrix(PlayerCamera::Zoom, static_cast<GLfloat>(DisplayManager::Width()),
                                         static_cast<GLfloat>(DisplayManager::Height()), NEAR_PLANE,
                                         FAR_PLANE);
}

glm::mat4 MasterRenderer::getProjectionMatrix() {
    return projectionMatrix;
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

void MasterRenderer::processAssimpEntity(AssimpEntity *scene) {
    AssimpMesh *model = scene->getModel();
    auto batchIterator = scenes->find(model);
    if (batchIterator != scenes->end()) {
        batchIterator->second.push_back(scene);
    } else {
        std::vector<AssimpEntity *> newBatch;
        newBatch.push_back(scene);
        (*scenes)[model] = newBatch;
    }
}

void MasterRenderer::processBoundingBox(Interactive *boxHolder) {
    auto boxColor = boxHolder->getBoundingBox()->getRawBoundingBox();
    auto batchIterator = boxes->find(boxColor);
    if (batchIterator != boxes->end()) {
        batchIterator->second.push_back(boxHolder);
    } else {
        std::vector<Interactive *> newBatch;
        newBatch.push_back(boxHolder);
        (*boxes)[boxColor] = newBatch;
    }
}

void MasterRenderer::renderScene(std::vector<Entity *> entities, std::vector<AssimpEntity *> aEntities,
                                 std::vector<Terrain *> terrains, std::vector<Light *> lights) {
    for (Terrain *ter : terrains) {
        processTerrain(ter);
    }

    for (Entity *ent : entities) {
        processEntity(ent);
    }

    for (AssimpEntity *scene : aEntities) {
        processAssimpEntity(scene);
    }

    render(lights);
}

void MasterRenderer::renderBoundingBoxes(std::vector<Interactive*> boxes) {
    for (Interactive *ent : boxes) {
        if (ent->getBoundingBox() != nullptr) {
            processBoundingBox(ent);
        }
    }
    render();
}

void MasterRenderer::render() {
    this->prepareBoundingBoxRender();
    bShader->start();

    bShader->loadViewPosition(camera);
    bShader->loadViewMatrix(camera->getViewMatrix());
    bShader->loadProjectionMatrix(MasterRenderer::createProjectionMatrix());
    bRenderer->render(boxes);

    boxes->clear();
    bShader->stop();
}

/**
 * @brief prepares and clears buffer and screen for each iteration of loop
 */
void MasterRenderer::prepareBoundingBoxRender() {
    // render
    // ------
    glClearColor(1.0f, 1.0f, 1.0f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}