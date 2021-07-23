//
// Created by Joseph Alai on 7/6/21.
//

#define PRINTXYZ(VEC){printf("%f, %f, %f\n", VEC[0], VEC[1], VEC[2]);};

#include "MainGameLoop.h"
#include "../Util/FileSystem.h"
#include "../Util/Utils.h"
#include "../Util/LightUtil.h"
#include "../RenderEngine/DisplayManager.h"
#include "../RenderEngine/EntityRenderer.h"
#include "../RenderEngine/ObjLoader.h"
#include "../RenderEngine/MasterRenderer.h"
#include "../Guis/GuiTexture.h"
#include "../Guis/GuiRenderer.h"
#include "../Toolbox/MousePicker.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../FontMeshCreator/TextMeshCreator.h"
#include "../FontMeshCreator/GUIText.h"
#include "../FontRendering/FontShader.h"
#include "../FontRendering/FontRenderer.h"

void RenderText(FontModel *font, FontShader *shader, FontType fontType, std::string text, float x, float y, float scale,
                glm::vec3 color);


void MainGameLoop::main() {

    // Initialite Display
    DisplayManager::createDisplay();

    // Initialize VAO / VBO Loader
    Loader *loader = new Loader();

    /**
     * Loader Textures and Models
     */
    ModelTexture *grassTexture;
    TexturedModel *staticGrass, *staticTree, *staticStall, *staticFluffyTree, *staticDragon, *staticFern, *staticLamp;

    ModelData lampData = OBJLoader::loadObjModel("lamp");
    staticLamp = new TexturedModel(loader->loadToVAO(&lampData), new ModelTexture("lamp", PNG));

    ModelData fernData = OBJLoader::loadObjModel("fern");
    staticFern = new TexturedModel(loader->loadToVAO(&fernData), new ModelTexture("fern", PNG));
    staticFern->getModelTexture()->setNumberOfRows(2);

    ModelData dragonData = OBJLoader::loadObjModel("dragon");;
    staticDragon = new TexturedModel(loader->loadToVAO(&dragonData), new ModelTexture("grassTexture", PNG));
    auto dragonEntity = new Entity(staticDragon, glm::vec3(0.0, 120.0, 80), glm::vec3(0.0f, 180.0f, 0.0f));

    ModelData grassData = OBJLoader::loadObjModel("grassModel");;
    grassTexture = new ModelTexture("grassTexture", PNG);
    grassTexture->setHasTransparency(true);
    grassTexture->setUseFakeLighting(true);
    staticGrass = new TexturedModel(loader->loadToVAO(&grassData), grassTexture);

    const Material material = Material{
            .shininess = 2.0f,
            .reflectivity = 2.0f
    };

    ModelData stallData = OBJLoader::loadObjModel("Stall");;
    staticStall = new TexturedModel(loader->loadToVAO(&stallData),
                                    new ModelTexture("stallTexture", PNG, material));
    ModelData treeData = OBJLoader::loadObjModel("tree");;
    staticTree = new TexturedModel(loader->loadToVAO(&treeData),
                                   new ModelTexture("tree", PNG, material));
    ModelData fluffyTreeData = OBJLoader::loadObjModel("fluffy-tree");
    staticFluffyTree = new TexturedModel(loader->loadToVAO(&fluffyTreeData),
                                         new ModelTexture("tree", PNG, material));

    Model *pBackpack = new Model("Backpack/backpack");



    /**
     * Entity holders to be rendered
     */
    std::vector<Terrain *> allTerrains;
    std::vector<Light *> lights;
    std::vector<Entity *> allEntities;
    std::vector<Scene *> allScenes;



    /**
     * Terrain Generation
     */

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

    Terrain *terrain = new Terrain(0, -1, loader, texturePack, blendMap, "heightMap");



    /**
     * Push back all terrains into the array
     */
    allTerrains.push_back(new Terrain(-1, -1, loader, texturePack, blendMap, "heightMap"));
    allTerrains.push_back(new Terrain(0, 0, loader, texturePack, blendMap, "heightMap"));
    allTerrains.push_back(new Terrain(-1, 0, loader, texturePack, blendMap, "heightMap"));
    allTerrains.push_back(terrain);


    /**
     * Light Generation
     */
    lights.push_back(new Light(glm::vec3(0.0, 1000., -7000.0f), glm::vec3(0.4f, 0.4f, 0.4f), {
            .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
            .diffuse =  glm::vec3(0.5f, 0.5f, 0.5f),
            .constant = Light::kDirectional,
            .linear = 0.09f,
            .quadratic = 0.032f
    }));
    auto d = LightUtil::AttenuationDistance(65);
    lights.push_back(new Light(glm::vec3(120.0f, terrain->getHeightOfTerrain(120, -50) + 10, -50.0f),
                               glm::vec3(0.0f, 0.0f, 2.0f),
                               {
                                       .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
                                       .diffuse =  glm::vec3(0.5f, 0.5f, 0.5f),
                                       .constant = d.x,
                                       .linear = d.y,
                                       .quadratic = d.z
                               }));
    lights.push_back(new Light(glm::vec3(100.0f, terrain->getHeightOfTerrain(100, -50) + 10, -50.0f),
                               glm::vec3(2.0f, 0.0f, 0.0f),
                               {
                                       .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
                                       .diffuse =  glm::vec3(0.5f, 0.5f, 0.5f),
                                       .constant = d.x,
                                       .linear = d.y,
                                       .quadratic = d.z
                               }));
    lights.push_back(new Light(glm::vec3(110.0f, terrain->getHeightOfTerrain(110, -20) + 10, -20.0f),
                               glm::vec3(0.0, 2.0, 0.0f),
                               {
                                       .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
                                       .diffuse =  glm::vec3(0.5f, 0.5f, 0.5f),
                                       .constant = d.x,
                                       .linear = d.y,
                                       .quadratic = d.z
                               }));



    /**
     * Load each entity into the vector, including position, scale, and rotation
     */
    Entity *lampy = new Entity(staticLamp, glm::vec3(120.0f, terrain->getHeightOfTerrain(120, -50), -50.0f));
    allEntities.push_back(lampy);
    allEntities.push_back(new Entity(staticStall, glm::vec3(1.0f, 0.0f, -82.4f), glm::vec3(0.0f, 180.0f, 0.0f)));
    allEntities.push_back(new Entity(staticLamp, glm::vec3(100.0f, terrain->getHeightOfTerrain(100, -50), -50.0f)));
    allEntities.push_back(new Entity(staticLamp, glm::vec3(110.0f, terrain->getHeightOfTerrain(110, -20), -20.0f)));


    for (int i = 0; i < 500; ++i) {
        allEntities.push_back(new Entity(staticGrass, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticFluffyTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticTree, generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(.25, 1.50)));
        allEntities.push_back(
                new Entity(staticFern, Utils::roll(1, 4), generateRandomPosition(terrain), generateRandomRotation(),
                           generateRandomScale(.25, 1.50)));
        if (i % 30 == 0) {
            allScenes.push_back(new Scene(pBackpack, generateRandomPosition(terrain, 3.0f), generateRandomRotation(),
                                          generateRandomScale(3.25, 10.50)));
        }
    }
    allEntities.push_back(dragonEntity);




    /**
     * Player Creation
     */
    RawModel *playerModel = loader->loadToVAO(&stallData);
    TexturedModel *playerOne = new TexturedModel(playerModel, new ModelTexture(
            "stallTexture", PNG));

    Player *player = new Player(playerOne, glm::vec3(100.0f, 3.0f, -50.0f), glm::vec3(0.0f, 180.0f, 0.0f), 1.0f);
    allEntities.push_back(player);
    PlayerCamera *playerCamera = new PlayerCamera(player);


    /**
     * GUI Creation
     */
    std::vector<GuiTexture *> guis = std::vector<GuiTexture *>();
    guis.push_back(new GuiTexture(loader->loadTexture("gui/lifebar")->getId(), glm::vec2(-0.72f, 0.9f),
                                  glm::vec2(0.290f, 0.0900f)));
    guis.push_back(new GuiTexture(loader->loadTexture("gui/green")->getId(), glm::vec2(-0.7f, 0.9f),
                                  glm::vec2(0.185f, 0.070f)));
    guis.push_back(new GuiTexture(loader->loadTexture("gui/heart")->getId(), glm::vec2(-0.9f, 0.9f),
                                  glm::vec2(0.075f, 0.075f)));


    /**
     * Renderers
     */
    MasterRenderer *renderer = new MasterRenderer(playerCamera, loader);
    GuiRenderer *guiRenderer = new GuiRenderer(loader);
    FontRenderer *fontRenderer = new FontRenderer();


    /**
     * Mouse Picker
     */
    MousePicker *picker = new MousePicker(playerCamera, renderer->getProjectionMatrix(), terrain);


    /**
     * Font Configuration
     */
    std::vector<GUIText *> *texts = new std::vector<GUIText *>();
    FontType font = TextMeshCreator::loadFont("arial", "arial");
    FontModel *fonty = loader->loadFontVAO(6, 4, sizeof(float));
    texts->push_back(new GUIText(fonty, &font, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f)));
    texts->push_back(new GUIText(fonty, &font, "Joseph Alai MCMXII", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f)));


    /**
     * Main Game Loop
     */
    while (DisplayManager::stayOpen()) {
        playerCamera->move(terrain);
        picker->update();

        glm::vec3 terrainPoint = picker->getCurrentTerrainPoint();

        if (terrainPoint != glm::vec3()) {
            lampy->setPosition(terrainPoint);
            lights[1]->setPosition(glm::vec3(terrainPoint.x, terrainPoint.y + 15.0f, terrainPoint.z));
        }

        for (Terrain *ter : allTerrains) {
            renderer->processTerrain(ter);
        }

        for (Entity *ent : allEntities) {
            renderer->processEntity(ent);
        }

        for (Scene *scene : allScenes) {
            renderer->processScenes(scene);
        }


        renderer->render(lights);
        guiRenderer->render(guis);
        fontRenderer->render(texts);

        DisplayManager::updateDisplay();
    }

    /**
     * Clean up renderers and loaders
     */
    fontRenderer->cleanUp();
    guiRenderer->cleanUp();
    renderer->cleanUp();
    loader->cleanUp();

    /**
     * Close display
     */
    DisplayManager::closeDisplay();
}

glm::vec3 MainGameLoop::generateRandomPosition(Terrain *terrain, float yOffset) {
    glm::vec3 positionVector(0.0f);
    positionVector.x = floor(Utils::randomFloat() * 1500 - 800);
    positionVector.z = floor(Utils::randomFloat() * -800);
    positionVector.y = terrain->getHeightOfTerrain(positionVector.x, positionVector.z) + yOffset;
    return positionVector;
}

glm::vec3 MainGameLoop::generateRandomRotation() {
    float rx, ry, rz, scale;
    rx = 0;
    ry = Utils::randomFloat() * 100 - 50;
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
    auto r = Utils::randomFloat() * multiplier;
    if (r < min) {
        r = min;
    }
    if (r > max) {
        r = max;
    }
    return r;
}