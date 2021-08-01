//
// Created by Joseph Alai on 7/6/21.
//

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
#include "../Util/Colors.h"
#include "../FontRendering/TextMaster.h"
#include "../Toolbox/TerrainPicker.h"
#include "../RenderEngine/FrameBuffers.h"
#include "../Interaction/InteractiveModel.h"

#include "../Util/CommonHeader.h"
void testCraftStuff(float x, float y, float z) {
    float result;
    PRINT_FOURLN("x, y, z = ", x, y, z);
    int nearestX = roundf(x);
    int nearestY = roundf(y);
    int nearestZ = roundf(z);
    PRINT_FOURLN("nearestX, nearestY, nearestZ: roundf(x), roundf(y), roundf(z)", nearestX, nearestY, nearestZ);
    float marginX = x - nearestX;
    float marginY = y - nearestY;
    float marginZ = z - nearestZ;
    PRINT_FOURLN("marginX, marginY, marginZ: (x - nearestX), (y - nearestY), (z - nearestZ):", marginX, marginY, marginZ);
    float padding = 0.25;
    for (int dy = 0; dy < 2; dy++) {
        if (marginX < -padding) {
            x = nearestX - padding;
        }
        if (marginX > padding) {
            x = nearestX + padding;
        }
        if (marginY < -padding ) {
            y = nearestY - padding;
            result = 1;
        }
        if (marginY > padding) {
            y = nearestY + padding;
            result = 1;
        }
        if (marginZ < -padding) {
            z = nearestZ - padding;
        }
        if (marginZ > padding) {
            z = nearestZ + padding;
        }
        PRINT_FOURLN("x, y, z", x, y, z);
    }
}
#include "../World/Block.h"
void testMap() {
    std::map<int, Block>a;
    a[1] = {1, 2, 3, 4};
    a[4] = {3, 4, 6, 2};
    a[29] = {3, 39, 12, 43};

    std::map<int, Block>::iterator  it2 = a.find(29120);
    if (it2 == a.end()) {
        std::cout << "could not find it." << std::endl;
    }

    std::map<int, Block>::iterator  it;
    for(it = a.begin(); it != a.end(); it++) {
        std::cout  << it->first << ": " << it->second.x << ", "<< it->second.y << ", "<< it->second.z << ", "<< it->second.w << ", " << std::endl;
    }
    std::cout << a[92108].x << ", " << a[92108].y << ", " << a[92108].z << ", " << a[92108].w << ", " << std::endl;
}

void MainGameLoop::main() {
    testMap();
    return;
    for (auto x:std::vector<float>{0, 0.25f, 0.3f, 0.4f, 0.49f, 0.51f, 0.6f, 0.75f, .9f, 1.0f, 1.1f, 1.4f}) {
        for (auto ynum:std::vector<float>{Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000}) {
            for (auto znum:std::vector<float>{Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000, Utils::randomFloat() * 1000}) {
                testCraftStuff(x, ynum, znum);
            }
        }
    }
//    testCraftStuff();
    return;

    // Initialite Display
    DisplayManager::createDisplay();

    // Initialize VAO / VBO Loader
    auto loader = new Loader();

    /**
     * Font Configuration
     */
    // Initialize Texting
    TextMaster::init(loader);

    auto fontRenderer = new FontRenderer();
    FontType arial = TextMeshData::loadFont("arial", 48);
    FontType noodle = TextMeshData::loadFont("noodle", 48);

    auto texts = new std::vector<GUIText *>();
    FontModel *fonty = loader->loadFontVAO();
    texts->push_back(new GUIText(
            "This is sample text because I know what I am doing whether you like it or not so I am joe.This is sample text because I know what I am doing whether you like it or not so I am joe.",
            0.50f, fonty, &noodle, glm::vec2(25.0f, 225.0f), Colors::Whitesmoke,
            0.50f * static_cast<float>(DisplayManager::Width()),
            false));
    texts->push_back(new GUIText("Joseph Alai MCMXII", 0.5f, fonty, &arial, glm::vec2(540.0f, 570.0f), Colors::Cyan,
                                 0.75f * static_cast<float>(DisplayManager::Width()), false));
    auto clickColorText = new GUIText("Color: ", 0.5f, fonty, &arial, glm::vec2(10.0f, 20.0f), Colors::Green,
                                      0.75f * static_cast<float>(DisplayManager::Width()), false);
    texts->push_back(clickColorText);

    /**
     * Loader Textures and Models
     */
    ModelTexture *grassTexture;

    ModelData lampData = OBJLoader::loadObjModel("lamp");
    // load bb version 1
    BoundingBoxData box = OBJLoader::loadBoundingBox("lamp"); // load by adding a new mesh to count as bounding box
    RawBoundingBox *pLampBox = loader->loadToVAO(box);
    auto staticLamp = new TexturedModel(loader->loadToVAO(lampData), new ModelTexture("lamp", PNG));


    // loading bb version 2
    ModelData fernData = OBJLoader::loadObjModel("fern");
    RawBoundingBox *pFernBox = loader->loadToVAO(OBJLoader::loadBoundingBox(fernData)); // load by previously loaded object
    auto staticFern = new TexturedModel(loader->loadToVAO(fernData), new ModelTexture("fern", PNG));
    staticFern->getModelTexture()->setNumberOfRows(2);

    ModelData grassData = OBJLoader::loadObjModel("grassModel");;
    RawBoundingBox *pGrassBox = loader->loadToVAO(OBJLoader::loadBoundingBox(grassData));
    grassTexture = new ModelTexture("grassTexture", PNG, true, true);
    auto staticGrass = new TexturedModel(loader->loadToVAO(grassData), grassTexture);

    const Material material = Material{
            .shininess = 2.0f,
            .reflectivity = 2.0f
    };

    ModelData stallData = OBJLoader::loadObjModel("Stall");;
    RawBoundingBox *pStallBox = loader->loadToVAO(OBJLoader::loadBoundingBox(stallData));
    auto staticStall = new TexturedModel(loader->loadToVAO(stallData),
                                         new ModelTexture("stallTexture", PNG, material));

    ModelData treeData = OBJLoader::loadObjModel("tree");;
    RawBoundingBox *pTreeBox = loader->loadToVAO(OBJLoader::loadBoundingBox(treeData));
    auto staticTree = new TexturedModel(loader->loadToVAO(treeData),
                                        new ModelTexture("tree", PNG, material));

    ModelData fluffyTreeData = OBJLoader::loadObjModel("fluffy-tree");
    RawBoundingBox *pFluffyTreeBox = loader->loadToVAO(OBJLoader::loadBoundingBox(fluffyTreeData));
    auto staticFluffyTree = new TexturedModel(loader->loadToVAO(fluffyTreeData),
                                              new ModelTexture("tree", PNG, material));

    auto pBackpack = new AssimpMesh("Backpack/backpack");

    /**
     * Entity holders to be rendered
     */
    std::vector<Terrain *> allTerrains;
    std::vector<Light *> lights;
    std::vector<Entity *> entities;
    std::vector<AssimpEntity *> scenes;
    std::vector<Interactive *> allBoxes;

    /**
     * Terrain Generation
     */
    auto backgroundTexture = new TerrainTexture(loader->loadTexture("MultiTextureTerrain/grass")->getId());
    auto rTexture = new TerrainTexture(loader->loadTexture("MultiTextureTerrain/dirt")->getId());
    auto gTexture = new TerrainTexture(loader->loadTexture("MultiTextureTerrain/blueflowers")->getId());
    auto bTexture = new TerrainTexture(loader->loadTexture("MultiTextureTerrain/brickroad")->getId());
    auto texturePack = new TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture);
    auto blendMap = new TerrainTexture(loader->loadTexture("MultiTextureTerrain/blendMap")->getId());
    auto terrain = new Terrain(0, -1, loader, texturePack, blendMap, "heightMap");

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
    auto lampy = new Entity(staticLamp, new BoundingBox(pLampBox, BoundingBoxIndex::genUniqueId()),
                            glm::vec3(120.0f, terrain->getHeightOfTerrain(120, -50), -50.0f));
    entities.push_back(lampy);
    entities.push_back(
            new Entity(staticStall, new BoundingBox(pLampBox, BoundingBoxIndex::genUniqueId()), glm::vec3(1.0f, 0.0f, -82.4f),
                       glm::vec3(0.0f, 180.0f, 0.0f)));
    entities.push_back(new Entity(staticLamp, new BoundingBox(pLampBox, BoundingBoxIndex::genUniqueId()),
                                  glm::vec3(100.0f, terrain->getHeightOfTerrain(100, -50), -50.0f)));
    entities.push_back(new Entity(staticLamp, new BoundingBox(pLampBox, BoundingBoxIndex::genUniqueId()),
                                  glm::vec3(110.0f, terrain->getHeightOfTerrain(110, -20), -20.0f)));


    for (int i = 0; i < 500; ++i) {
        entities.push_back(
                new Entity(staticGrass, new BoundingBox(pGrassBox, BoundingBoxIndex::genUniqueId()), generateRandomPosition(terrain),
                           generateRandomRotation(),
                           generateRandomScale(0.5, 1.50f)));
        entities.push_back(new Entity(staticFluffyTree, new BoundingBox(pFluffyTreeBox,
                                                                        BoundingBoxIndex::genUniqueId()),
                                      generateRandomPosition(terrain), generateRandomRotation(),
                                      generateRandomScale(0.5, 1.50f)));
        entities.push_back(
                new Entity(staticTree, new BoundingBox(pTreeBox, BoundingBoxIndex::genUniqueId()), generateRandomPosition(terrain),
                           generateRandomRotation(),
                           generateRandomScale(.25, 1.50)));
        entities.push_back(
                new Entity(staticFern, new BoundingBox(pFernBox, BoundingBoxIndex::genUniqueId()), Utils::roll(1, 4),
                           generateRandomPosition(terrain), generateRandomRotation(),
                           generateRandomScale(.25, 1.50)));
        if (i % 30 == 0) {
            auto pBackpackBox = OBJLoader::loadBoundingBox(pBackpack);
            auto pBackpackBoxs = loader->loadToVAO(pBackpackBox);
            scenes.push_back(
                    new AssimpEntity(pBackpack, new BoundingBox(pBackpackBoxs, BoundingBoxIndex::genUniqueId()), generateRandomPosition(terrain, 3.0f), generateRandomRotation(),
                                     generateRandomScale(3.25, 10.50)));
        }
    }

    /**
     * Player Creation
     */
    RawModel *playerModel = loader->loadToVAO(stallData);
    auto playerOne = new TexturedModel(playerModel, new ModelTexture(
            "stallTexture", PNG));

    auto player = new Player(playerOne, new BoundingBox(pStallBox, BoundingBoxIndex::genUniqueId()), glm::vec3(100.0f, 3.0f, -50.0f),
                             glm::vec3(0.0f, 180.0f, 0.0f), 1.0f);
    InteractiveModel::setInteractiveBox(player);
    entities.push_back(player);
    auto playerCamera = new PlayerCamera(player);

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
    auto renderer = new MasterRenderer(playerCamera, loader);
    auto guiRenderer = new GuiRenderer(loader);

    /**
     * Framebuffers
     */
    auto reflectFbo = new FrameBuffers();
    auto gui = new GuiTexture(reflectFbo->getReflectionTexture(), glm::vec2(-0.25f - 0.25f), glm::vec2(0.3f));
    guis.push_back(gui);

    /**
     * Mouse Picker
     */
    auto picker = new TerrainPicker(playerCamera, renderer->getProjectionMatrix(), terrain);

    for (auto e: entities) {
        if (e->getBoundingBox() != nullptr) {
            allBoxes.push_back(e);
        }
    }
    allBoxes.reserve(entities.size() + scenes.size() );
    allBoxes.insert(allBoxes.end(), entities.begin(), entities.end());
    allBoxes.insert(allBoxes.end(), scenes.begin(), scenes.end());

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

        if (InputMaster::hasPendingClick()) {
            if (InputMaster::mouseClicked(LeftClick)) {
                renderer->renderBoundingBoxes(allBoxes);
                glm::vec3 clickColor = Picker::getColor();
                int element = BoundingBoxIndex::getIndexByColor(clickColor);
                *clickColorText = GUIText(Colors::toString(clickColor) + ", Element: " + std::to_string(element),
                                          0.5f, fonty, &noodle, glm::vec2(10.0f, 20.0f), clickColor / 255.0f,
                                          0.75f * static_cast<float>(DisplayManager::Width()), false);
                Interactive *pClickedModel = InteractiveModel::getInteractiveBox(BoundingBoxIndex::getIndexByColor(clickColor));
                if (pClickedModel != nullptr) {
                    if (auto a = dynamic_cast<Player *>(pClickedModel)) {
                        if (!a->hasMaterial()) {
                            a->setMaterial({500.0f, 500.0f});
                            a->activateMaterial();
                        } else {
                            a->disableMaterial();
                        }
                    }
                    printf("position: x, y, z: (%f, %f, %f)\n", pClickedModel->getPosition().x, pClickedModel->getPosition().y, pClickedModel->getPosition().z);
                }
                InputMaster::resetClick();
            }
        }

        // framebuffer only
        reflectFbo->bindReflectionFrameBuffer();
        {
            renderer->renderBoundingBoxes(allBoxes);
        }
        reflectFbo->unbindCurrentFrameBuffer();

        // non framebuffer
        {
            renderer->renderScene(entities, scenes, allTerrains, lights);
        }


        TextMaster::render();
        guiRenderer->render(guis);
        DisplayManager::updateDisplay();


    }
    /**
     * Clean up renderers and loaders
     */
    reflectFbo->cleanUp();
    TextMaster::cleanUp();
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
    float rx, ry, rz;
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