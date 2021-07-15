//
// Created by Joseph Alai on 7/6/21.
//

#define PRINTXYZ(VEC){printf("%f, %f, %f\n", VEC[0], VEC[1], VEC[2]);};

#include "MainGameLoop.h"
#include "../Toolbox/FileSystem.h"
#include "../Toolbox/Utils.h"
#include "../RenderEngine/DisplayManager.h"
#include "../RenderEngine/Loader.h"
#include "../RenderEngine/EntityRenderer.h"
#include "../RenderEngine/ObjLoader.h"
#include "../RenderEngine/MasterRenderer.h"

using namespace glm;

void MainGameLoop::main() {

    DisplayManager::createDisplay();

    Loader *loader;

    loader = new Loader();


    TerrainTexture *backgroundTexture = new TerrainTexture(
            loader->loadTexture(FileSystem::Path("/src/Resources/Models/Terrain/MultiTexture/grass.png"))->getId());
    TerrainTexture *rTexture = new TerrainTexture(
            loader->loadTexture(FileSystem::Path("/src/Resources/Models/Terrain/MultiTexture/dirt.png"))->getId());
    TerrainTexture *gTexture = new TerrainTexture(loader->loadTexture(
            FileSystem::Path("/src/Resources/Models/Terrain/MultiTexture/blueflowers.png"))->getId());
    TerrainTexture *bTexture = new TerrainTexture(
            loader->loadTexture(FileSystem::Path("/src/Resources/Models/Terrain/MultiTexture/brickroad.png"))->getId());
    TerrainTexturePack *texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
    TerrainTexture *blendMap = new TerrainTexture(
            loader->loadTexture(FileSystem::Path("/src/Resources/Models/Terrain/MultiTexture/blendMap.png"))->getId());

    Terrain *terrain;
//    Terrain *terrain2;

    RawModel *grassModel, *treeModel, *fluffyTreeModel, *stallModel, *dragonModel;
    ModelTexture *grassTexture, *treeTexture, *fluffyTreeTexture, *stallTexture, *dragonTexture;
    TexturedModel *staticGrass, *staticTree, *staticStall, *staticFluffyTree, *staticDragon;
    Light *light;

    light = new Light(glm::vec3(0.0, 4.5, -10.0f), glm::vec3(1, 1, 1));


    ModelData dragonData = OBJLoader::loadObjModel("/src/Resources/Models/Tutorial/dragon.obj");
    dragonModel = loader->loadToVAO(&dragonData);
    dragonTexture = new ModelTexture(FileSystem::Path("/src/Resources/Models/Tutorial/grassTexture.png"), PNG);
    staticDragon = new TexturedModel(dragonModel, dragonTexture);
    auto dragonEntity = new Entity(staticDragon, glm::vec3(0.0, 120.0, 80), glm::vec3(0.0f, 180.0f, 0.0f));

    ModelData grassData = OBJLoader::loadObjModel("/src/Resources/Models/Tutorial/grassModel.obj");
    grassModel = loader->loadToVAO(&grassData);
    grassTexture = new ModelTexture(FileSystem::Path("/src/Resources/Models/Tutorial/grassTexture.png"), PNG);
    staticGrass = new TexturedModel(grassModel, grassTexture);
    grassTexture->setHasTransparency(true);
    grassTexture->setUseFakeLighting(true);


    ModelData stallData = OBJLoader::loadObjModel("/src/Resources/Models/Stall/Stall.obj");
    stallModel = loader->loadToVAO(&stallData);
    stallTexture = new ModelTexture(FileSystem::Path("/src/Resources/Models/Stall/stallTexture.png"), PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticStall = new TexturedModel(stallModel, stallTexture);

    ModelData treeData = OBJLoader::loadObjModel("/src/Resources/InProgress/Tree/tree.obj");
    treeModel = loader->loadToVAO(&treeData);
    treeTexture = new ModelTexture(FileSystem::Path("/src/Resources/InProgress/Tree/tree.png"), PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticTree = new TexturedModel(treeModel, treeTexture);

    ModelData fluffyTreeData = OBJLoader::loadObjModel("/src/Resources/InProgress/Tree/fluffy-tree.obj");
    fluffyTreeModel = loader->loadToVAO(&fluffyTreeData);
    fluffyTreeTexture = new ModelTexture(FileSystem::Path("/src/Resources/InProgress/Tree/tree.png"), PNG, Material{
            .ambient =  glm::vec3(1),
            .diffuse =  glm::vec3(1),
            .specular =  glm::vec3(0.3),
            .shininess = 32.0f});
    staticFluffyTree = new TexturedModel(fluffyTreeModel, fluffyTreeTexture);

    std::vector<Entity *> allEntities;
    allEntities.push_back(new Entity(staticStall, glm::vec3(1.0f, 0.0f, -82.4f), glm::vec3(0.0f, 180.0f, 0.0f)));

    terrain = new Terrain(0, -1, loader, texturePack, blendMap,
                          FileSystem::Path("/src/Resources/Models/Tutorial/heightMap.png"));
//    terrain2 = new Terrain(0, -1, loader, texturePack, blendMap, FileSystem::Path("/src/Resources/Models/Tutorial/heightMap.png"));

    for (int i = 0; i < 500; ++i) {
        allEntities.push_back(new Entity(staticGrass, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticFluffyTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(.25, 1.50)));
    }
    allEntities.push_back(dragonEntity);


    RawModel *playerModel = loader->loadToVAO(&stallData);
    TexturedModel *playerOne = new TexturedModel(playerModel, new ModelTexture(
            FileSystem::Path("/src/Resources/Models/Stall/stallTexture.png"), PNG));

    Player *player = new Player(playerOne, glm::vec3(100.0f, 3.0f, -50.0f), glm::vec3(0.0f), 1.0f);
    PlayerCamera *playerCamera = new PlayerCamera(player);
    allEntities.push_back(player);

    MasterRenderer *renderer;
    renderer = new MasterRenderer(playerCamera);
    while (DisplayManager::stayOpen()) {
        playerCamera->move(terrain);

        renderer->processTerrain(terrain);

        for (Entity *ent : allEntities) {
            renderer->processEntity(ent);
        }

        light->addToPosition(glm::vec3(0.0, 0.1 * sin(glfwGetTime()) * 2 + 0.005, cos(glfwGetTime()) * 2 * -0.1f - 0.1f));
        renderer->render(light);
        dragonEntity->setPosition(light->getPosition());
        DisplayManager::updateDisplay();
    }

    renderer->cleanUp();
    loader->cleanUp();
    DisplayManager::closeDisplay();
}

glm::vec3 MainGameLoop::generateRandomPosition(Terrain *terrain) {
    glm::vec3 positionVector(0.0f);
    positionVector.x = floor(randomFloat() * 1500 - 800);
    positionVector.z = floor(randomFloat() * -800);
    positionVector.y = terrain->getHeightOfTerrain(positionVector.x, positionVector.z);
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