//
// Created by Joseph Alai on 7/6/21.
//

#define PRINTXYZ(VEC){printf("%f, %f, %f\n", VEC[0], VEC[1], VEC[2]);};

#include "MainGameLoop.h"
#include "../Toolbox/FileSystem.h"
#include "../Toolbox/Utils.h"
#include "../RenderEngine/DisplayManager.h"
#include "../RenderEngine/EntityRenderer.h"
#include "../RenderEngine/ObjLoader.h"
#include "../RenderEngine/MasterRenderer.h"
#include "../Guis/GuiTexture.h"
#include "../Guis/GuiRenderer.h"
#include "glm/gtc/type_ptr.hpp"

void MainGameLoop::main() {
    DisplayManager::createDisplay();

    Loader *loader;

    loader = new Loader();

    TerrainTexture *backgroundTexture = new TerrainTexture(
            loader->loadTexture("MultiTextureTerrain/grass")->getId());
    TerrainTexture *rTexture = new TerrainTexture(
            loader->loadTexture("MultiTextureTerrain/dirt")->getId());
    TerrainTexture *gTexture = new TerrainTexture(loader->loadTexture(
            "MultiTextureTerrain/blueflowers")->getId());
    TerrainTexture *bTexture = new TerrainTexture(
            loader->loadTexture("MultiTextureTerrain/brickroad")->getId());
    TerrainTexturePack *texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
    TerrainTexture *blendMap = new TerrainTexture(
            loader->loadTexture("MultiTextureTerrain/blendMap")->getId());

    Terrain *terrain;
//    Terrain *terrain2;

    RawModel *grassModel, *treeModel, *fluffyTreeModel, *stallModel, *dragonModel, *fernModel;
    ModelTexture *grassTexture, *treeTexture, *fluffyTreeTexture, *stallTexture, *dragonTexture, *fernTexture;
    TexturedModel *staticGrass, *staticTree, *staticStall, *staticFluffyTree, *staticDragon, *staticFern;
    std::vector<Light *>lights;
    Light *light = new Light(glm::vec3(0.0, 4.5, -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    lights.push_back(light);
    ModelData fernData = OBJLoader::loadObjModel("fern");
    fernModel = loader->loadToVAO(&fernData);
    fernTexture = new ModelTexture("fern", PNG);
    fernTexture->setNumberOfRows(2);
    staticFern = new TexturedModel(fernModel, fernTexture);

    // x rays abdomen, blood tests

    ModelData dragonData = OBJLoader::loadObjModel("dragon");;
    dragonModel = loader->loadToVAO(&dragonData);
    dragonTexture = new ModelTexture("grassTexture", PNG);
    staticDragon = new TexturedModel(dragonModel, dragonTexture);
    auto dragonEntity = new Entity(staticDragon, glm::vec3(0.0, 120.0, 80), glm::vec3(0.0f, 180.0f, 0.0f));

    ModelData grassData = OBJLoader::loadObjModel("grassModel");;
    grassModel = loader->loadToVAO(&grassData);
    grassTexture = new ModelTexture("grassTexture", PNG);
    grassTexture->setHasTransparency(true);
    grassTexture->setUseFakeLighting(true);
    staticGrass = new TexturedModel(grassModel, grassTexture);

    ModelData stallData = OBJLoader::loadObjModel("Stall");;
    stallModel = loader->loadToVAO(&stallData);
    stallTexture = new ModelTexture("stallTexture", PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticStall = new TexturedModel(stallModel, stallTexture);

    ModelData treeData = OBJLoader::loadObjModel("tree");;
    treeModel = loader->loadToVAO(&treeData);
    treeTexture = new ModelTexture("tree", PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticTree = new TexturedModel(treeModel, treeTexture);

    ModelData fluffyTreeData = OBJLoader::loadObjModel("fluffy-tree");
    fluffyTreeModel = loader->loadToVAO(&fluffyTreeData);
    fluffyTreeTexture = new ModelTexture("tree", PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticFluffyTree = new TexturedModel(fluffyTreeModel, fluffyTreeTexture);

    std::vector<Entity *> allEntities;
    allEntities.push_back(new Entity(staticStall, glm::vec3(1.0f, 0.0f, -82.4f), glm::vec3(0.0f, 180.0f, 0.0f)));

    terrain = new Terrain(0, -1, loader, texturePack, blendMap,
                          "heightMap");
//    terrain2 = new Terrain(0, -1, loader, texturePack, blendMap, "heightMap");

    for (int i = 0; i < 500; ++i) {
        allEntities.push_back(new Entity(staticGrass, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticFluffyTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(.25, 1.50)));
        allEntities.push_back(new Entity(staticFern, roll(1, 4), generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(.25, 1.50)));
    }
    allEntities.push_back(dragonEntity);


    RawModel *playerModel = loader->loadToVAO(&stallData);
    TexturedModel *playerOne = new TexturedModel(playerModel, new ModelTexture(
            "stallTexture", PNG));

    Player *player = new Player(playerOne, glm::vec3(100.0f, 3.0f, -50.0f), glm::vec3(0.0f, 180.0f, 0.0f), 1.0f);
    allEntities.push_back(player);
    PlayerCamera *playerCamera = new PlayerCamera(player);


    std::vector<GuiTexture*> guis = std::vector<GuiTexture*>();
    guis.push_back(new GuiTexture(loader->loadTexture("gui/lifebar")->getId(), glm::vec2(-0.72f, 0.9f), glm::vec2(0.290f, 0.0900f)));
    guis.push_back(new GuiTexture(loader->loadTexture("gui/green")->getId(), glm::vec2(-0.7f, 0.9f), glm::vec2(0.185f, 0.070f)));
    guis.push_back(new GuiTexture(loader->loadTexture("gui/heart")->getId(), glm::vec2(-0.9f, 0.9f), glm::vec2(0.075f, 0.075f)));

    GuiRenderer *guiRenderer = new GuiRenderer(loader);

    MasterRenderer *renderer;
    renderer = new MasterRenderer(playerCamera);
    while (DisplayManager::stayOpen()) {
        playerCamera->move(terrain);
        renderer->processTerrain(terrain);

        for (Entity *ent : allEntities) {
            renderer->processEntity(ent);
        }

        light->setPosition(light->getPosition() + glm::vec3(0.0, 0.01, -0.1f));
        dragonEntity->setPosition(light->getPosition());
        renderer->render(lights);
        guiRenderer->render(guis);
        DisplayManager::updateDisplay();
    }
    guiRenderer->cleanUp();
    renderer->cleanUp();
    loader->cleanUp();
    DisplayManager::closeDisplay();
}

glm::vec3 MainGameLoop::generateRandomPosition(Terrain *terrain, float yOffset) {
    glm::vec3 positionVector(0.0f);
    positionVector.x = floor(randomFloat() * 1500 - 800);
    positionVector.z = floor(randomFloat() * -800);
    positionVector.y = terrain->getHeightOfTerrain(positionVector.x, positionVector.z) + yOffset;
    return positionVector;
}

glm::vec3 MainGameLoop::generateRandomRotation() {
    float rx, ry, rz, scale;
    rx = 0;
    ry = randomFloat() * 100 - 50;
    rz = 0;
    glm::vec3 rot(rx, ry, rz);
    rot = rot * 180.0f;
    return rot;
}

float MainGameLoop::generateRandomScale(float min = 0.75, float max = 1.50) {
    float multiplier = 1;
    if (max > 1) {
        multiplier = ceil(max);
    }
    auto r = randomFloat() * multiplier;
    if (r < min) {
        r = min;
    }
    if (r > max) {
        r = max;
    }
    return r;
}