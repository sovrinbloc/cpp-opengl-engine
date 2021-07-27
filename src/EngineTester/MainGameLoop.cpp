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
#include "../FontMeshCreator/TextMeshData.h"
#include "../FontMeshCreator/GUIText.h"
#include "../FontRendering/FontRenderer.h"
#include "../Util/ColorNames.h"
#include "../FontRendering/TextMaster.h"
#include "../Toolbox/TerrainPicker.h"
#include "../RenderEngine/FrameBuffers.h"

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);

void saveScreenshotToFile(const std::string &filename, int windowWidth, int windowHeight);


void MainGameLoop::main() {

    // Initialite Display
    DisplayManager::createDisplay();

    // Initialize VAO / VBO Loader
    Loader *loader = new Loader();


    /**
     * Font Configuration
     */
    // Initialize Texting
    TextMaster::init(loader);

    FontRenderer *fontRenderer = new FontRenderer();
    FontType arial = TextMeshData::loadFont("arial", 48);
    FontType noodle = TextMeshData::loadFont("noodle", 48);

    std::vector<GUIText *> *texts = new std::vector<GUIText *>();
    FontModel *fonty = loader->loadFontVAO();
    texts->push_back(new GUIText(
            "This is sample text because I know what I am doing whether you like it or not so I am joe.This is sample text because I know what I am doing whether you like it or not so I am joe.",
            0.50f, fonty, &noodle, glm::vec2(25.0f, 225.0f), ColorNames::Whitesmoke, 0.50f * DisplayManager::Width(),
            false));
    texts->push_back(new GUIText("Joseph Alai MCMXII", 0.5f, fonty, &arial, glm::vec2(540.0f, 570.0f), ColorNames::Cyan,
                                 0.75f * DisplayManager::Width(), false));


    /**
     * Loader Textures and Models
     */
    ModelTexture *grassTexture;
    TexturedModel *staticGrass, *staticTree, *staticStall, *staticFluffyTree, *staticDragon, *staticFern, *staticLamp;

    ModelData lampData = OBJLoader::loadObjModel("lamp");
    RawBoundingBox *pLampBox = loader->loadToVAO(lampData.getBoundingBox());
    staticLamp = new TexturedModel(loader->loadToVAO(&lampData), new ModelTexture("lamp", PNG));

    ModelData fernData = OBJLoader::loadObjModel("fern");
    RawBoundingBox *pFernBox = loader->loadToVAO(fernData.getBoundingBox());
    staticFern = new TexturedModel(loader->loadToVAO(&fernData), new ModelTexture("fern", PNG));
    staticFern->getModelTexture()->setNumberOfRows(2);

    ModelData dragonData = OBJLoader::loadObjModel("dragon");;
    RawBoundingBox *pDragonBox = loader->loadToVAO(dragonData.getBoundingBox());
    staticDragon = new TexturedModel(loader->loadToVAO(&dragonData), new ModelTexture("grassTexture", PNG));
    auto dragonEntity = new Entity(staticDragon, new BoundingBox(pDragonBox, glm::vec3(0.0f, 0.0f, 0.0f)),
                                   glm::vec3(0.0, 120.0, 80), glm::vec3(0.0f, 180.0f, 0.0f));

    ModelData grassData = OBJLoader::loadObjModel("grassModel");;
    RawBoundingBox *pGrassBox = loader->loadToVAO(grassData.getBoundingBox());
    grassTexture = new ModelTexture("grassTexture", PNG);
    grassTexture->setHasTransparency(true);
    grassTexture->setUseFakeLighting(true);
    staticGrass = new TexturedModel(loader->loadToVAO(&grassData), grassTexture);


    const Material material = Material{
            .shininess = 2.0f,
            .reflectivity = 2.0f
    };

    ModelData stallData = OBJLoader::loadObjModel("Stall");;
    RawBoundingBox *pStallBox = loader->loadToVAO(stallData.getBoundingBox());
    staticStall = new TexturedModel(loader->loadToVAO(&stallData),
                                    new ModelTexture("stallTexture", PNG, material));

    ModelData treeData = OBJLoader::loadObjModel("tree");;
    RawBoundingBox *pTreeBox = loader->loadToVAO(treeData.getBoundingBox());
    staticTree = new TexturedModel(loader->loadToVAO(&treeData),
                                   new ModelTexture("tree", PNG, material));
    ModelData fluffyTreeData = OBJLoader::loadObjModel("fluffy-tree");
    RawBoundingBox *pFluffyTreeBox = loader->loadToVAO(fluffyTreeData.getBoundingBox());
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
    auto d = LightUtil::AttenuationDistance(65);
    Lighting l = Lighting{glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), d.x, d.y, d.z};
    lights.push_back(new Light(glm::vec3(0.0, 1000., -7000.0f), glm::vec3(0.4f, 0.4f, 0.4f), {
            .ambient =  glm::vec3(0.2f, 0.2f, 0.2f),
            .diffuse =  glm::vec3(0.5f, 0.5f, 0.5f),
            .constant = Light::kDirectional,
    }));
    lights.push_back(new Light(glm::vec3(120.0f, terrain->getHeightOfTerrain(120, -50) + 10, -50.0f),
                               glm::vec3(0.0f, 0.0f, 2.0f), l));
    lights.push_back(new Light(glm::vec3(100.0f, terrain->getHeightOfTerrain(100, -50) + 10, -50.0f),
                               glm::vec3(2.0f, 0.0f, 0.0f), l));
    lights.push_back(new Light(glm::vec3(110.0f, terrain->getHeightOfTerrain(110, -20) + 10, -20.0f),
                               glm::vec3(0.0, 2.0, 0.0f), l));



    /**
     * Load each entity into the vector, including position, fontSize, and rotation
     */
    Entity *lampy = new Entity(staticLamp, new BoundingBox(pLampBox, glm::vec3(0.01f)),
                               glm::vec3(120.0f, terrain->getHeightOfTerrain(120, -50), -50.0f));
    allEntities.push_back(lampy);
    allEntities.push_back(
            new Entity(staticStall, new BoundingBox(pLampBox, glm::vec3(0.02f)), glm::vec3(1.0f, 0.0f, -82.4f),
                       glm::vec3(0.0f, 180.0f, 0.0f)));
    allEntities.push_back(new Entity(staticLamp, new BoundingBox(pLampBox, glm::vec3(0.03f)),
                                     glm::vec3(100.0f, terrain->getHeightOfTerrain(100, -50), -50.0f)));
    allEntities.push_back(new Entity(staticLamp, new BoundingBox(pLampBox, glm::vec3(0.04f)),
                                     glm::vec3(110.0f, terrain->getHeightOfTerrain(110, -20), -20.0f)));


    for (int i = 0; i < 500; ++i) {
        allEntities.push_back(
                new Entity(staticGrass, new BoundingBox(pGrassBox, glm::vec3(0.05f)), generateRandomPosition(terrain),
                           generateRandomRotation(),
                           generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(new Entity(staticFluffyTree, new BoundingBox(pFluffyTreeBox, glm::vec3(0.06f)),
                                         generateRandomPosition(terrain), generateRandomRotation(),
                                         generateRandomScale(0.5, 1.50f)));
        allEntities.push_back(
                new Entity(staticTree, new BoundingBox(pTreeBox, glm::vec3(0.07f)), generateRandomPosition(terrain),
                           generateRandomRotation(),
                           generateRandomScale(.25, 1.50)));
        allEntities.push_back(
                new Entity(staticFern, new BoundingBox(pFernBox, glm::vec3(0.08f)), Utils::roll(1, 4),
                           generateRandomPosition(terrain), generateRandomRotation(),
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

    Player *player = new Player(playerOne, new BoundingBox(pStallBox, glm::vec3(1.0f)), glm::vec3(100.0f, 3.0f, -50.0f),
                                glm::vec3(0.0f, 180.0f, 0.0f), 1.0f);
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

    // Framebuffer
    FrameBuffers *fbos = new FrameBuffers();
    GuiTexture *gui = new GuiTexture(fbos->getReflectionTexture(), glm::vec2(-0.5f -0.5f), glm::vec2(0.5f, 0.5f));
//    guis.push_back(gui);

    /**
     * Mouse Picker
     */
    TerrainPicker *picker = new TerrainPicker(playerCamera, renderer->getProjectionMatrix(), terrain);



    bool done = false;
    /**
     * Main Game Loop
     */
    while (DisplayManager::stayOpen()) {
        playerCamera->move(terrain);

        picker->update();

        glm::vec3 terrainPoint = picker->getCurrentTerrainPoint();

//        if (terrainPoint != glm::vec3()) {
//            lampy->setPosition(terrainPoint);
//            lights[1]->setPosition(glm::vec3(terrainPoint.x, terrainPoint.y + 15.0f, terrainPoint.z));
//        }

        for (Terrain *ter : allTerrains) {
            renderer->processTerrain(ter);
        }

        //framebuffer only
        fbos->bindReflectionFrameBuffer();
        for (Entity *ent : allEntities) {
            renderer->processEntity(ent);
        }
        fbos->unbindCurrentFrameBuffer();



        for (Entity *ent : allEntities) {
            renderer->processEntity(ent);
        }

        for (Scene *scene : allScenes) {
            renderer->processScenes(scene);
        }


        renderer->render(lights);

        guiRenderer->render(guis);
        TextMaster::render();
        DisplayManager::updateDisplay();

//        const glm::vec3 &colors = InputMaster::getClicked(renderer->getProjectionMatrix(), playerCamera->GetViewMatrix());
//        for (Entity *ent : allEntities) {
//            renderer->processBoundingBox(ent);
//        }

        if (InputMaster::hasPendingClick()) {
            if (InputMaster::mouseClicked(LeftClick)) {
                saveScreenshotToFile("output" + std::to_string(glfwGetTime() / 10) + std::string(".tga"),
                                     DisplayManager::Width(), DisplayManager::Height());
            }
        }
        done = true;


        unsigned char pixel[3];
        glFlush();
        glFinish();
        glReadPixels(static_cast<int>(InputMaster::mouseX),
                     static_cast<int>(static_cast<float>(DisplayManager::Height()) - InputMaster::mouseY), 1, 1, GL_RGB,
                     GL_UNSIGNED_BYTE, pixel);
        glm::vec3 colors = glm::vec3(pixel[0], pixel[1], pixel[2]);
        if (colors.x != -1.0f) {
            InputMaster::resetClick();
        }

    }
    /**
     * Clean up renderers and loaders
     */
    fbos->cleanUp();
    TextMaster::cleanUp(); // added todo: implement
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

void saveScreenshotToFile(const std::string &filename, int windowWidth, int windowHeight) {
    const int numberOfPixels = windowWidth * windowHeight * 3;
    unsigned char pixels[numberOfPixels];

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    FILE *outputFile = fopen(filename.c_str(), "w");
    short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};

    fwrite(&header, sizeof(header), 1, outputFile);
    fwrite(pixels, numberOfPixels, 1, outputFile);
    fclose(outputFile);

    printf("Finish writing to file.\n");
}
