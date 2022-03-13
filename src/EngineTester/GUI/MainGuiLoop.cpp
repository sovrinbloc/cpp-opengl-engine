//
// Created by Joseph Alai on 3/9/22.
//

#include "MainGuiLoop.h"

#include "../../Util/FileSystem.h"
#include "../../Util/Utils.h"
#include "../../Util/LightUtil.h"
#include "../../RenderEngine/DisplayManager.h"
#include "../../RenderEngine/EntityRenderer.h"
#include "../../RenderEngine/ObjLoader.h"
#include "../../RenderEngine/MasterRenderer.h"
#include "../../Guis/Texture/GuiTexture.h"
#include "../../Guis/Texture/Rendering/GuiRenderer.h"
#include "../../Guis/Rect/Rendering/RectRenderer.h"
#include "../../Toolbox/MousePicker.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../Guis/Text/Rendering/FontRenderer.h"
#include "../../Util/ColorName.h"
#include "../../Guis/Text/Rendering/TextMaster.h"
#include "../../Toolbox/TerrainPicker.h"
#include "../../RenderEngine/FrameBuffers.h"
#include "../../Interaction/InteractiveModel.h"
#include "../../Util/CommonHeader.h"
#include "../../Guis/UiMaster.h"
#include "../../Guis/Constraints/UiPercentConstraint.h"
#include "../../Guis/Constraints/UiPixelConstraint.h"

// test to load objects.
#include <thread>

void MainGuiLoop::main() {

    // Initialite Display
    DisplayManager::createDisplay();

    // Initialize VAO / VBO Loader
    auto loader = new Loader();

    /**
     * Loader Textures and Models
     */
    ModelData stallData;
    BoundingBoxData stallBbData;

    /**
     * Load the models concurrently
     */
    auto f = [](ModelData *pModelData, BoundingBoxData *pBbData, const std::string &filename) {
        *pModelData = OBJLoader::loadObjModel(filename);
        *pBbData = OBJLoader::loadBoundingBox(*pModelData, ClickBoxTypes::BOX, BoundTypes::AABB);
    };

    std::vector<std::thread> vThreads;

    std::vector<const std::string> modelFiles = {"Stall"};
    std::vector<ModelData *> modelDatas = {&stallData};
    std::vector<BoundingBoxData *> bbDatas = {&stallBbData};

    for (int i = 0; i < modelDatas.size(); ++i) {
        std::thread thread(f, modelDatas[i], bbDatas[i], modelFiles[i]);
        vThreads.push_back(std::move(thread));
    }

    for (auto &&modelThread : vThreads) {
        (modelThread).join();
    }

    /**
     * End loading the models concurrently.
     */
    // load bb version 1

    const Material material = Material{
            .shininess = 2.0f,
            .reflectivity = 2.0f
    };

    RawBoundingBox *pStallBox = loader->loadToVAO(stallBbData);
    auto staticStall = new TexturedModel(loader->loadToVAO(stallData),
                                         new ModelTexture("stallTexture", PNG, material));

    /**
     * Entity holders to be rendered
     */
    std::vector<Terrain *> allTerrains;
    std::vector<Light *> lights;
    std::vector<Entity *> entities;
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

    /**
     * Player Creation
     */
    RawModel *playerModel = loader->loadToVAO(stallData);
    auto playerOne = new TexturedModel(playerModel, new ModelTexture(
            "stallTexture", PNG));

    auto player = new Player(playerOne, new BoundingBox(pStallBox, BoundingBoxIndex::genUniqueId()),
                             glm::vec3(100.0f, 3.0f, -50.0f),
                             glm::vec3(0.0f, 180.0f, 0.0f), 1.0f);

    InteractiveModel::setInteractiveBox(player);
    entities.push_back(player);
    auto playerCamera = new PlayerCamera(player);




    /**
     * Renderers
     */
    auto fontRenderer = new FontRenderer();
    auto renderer = new MasterRenderer(playerCamera, loader);
    auto guiRenderer = new GuiRenderer(loader);
    auto rectRenderer = new RectRenderer(loader);


    /**
     * GUI Creation
     */
    // initializes the UiMaster with these renderers.
    UiMaster::initialize(loader, guiRenderer, fontRenderer, rectRenderer);

    std::vector<GuiTexture *> guis = std::vector<GuiTexture *>();
    auto *guiHeart1 = new GuiTexture(loader->loadTexture("gui/lifebar")->getId(), glm::vec2(-0.72f, 0.9f),
                                     glm::vec2(0.290f, 0.0900f));
    auto *guiGreenBar = new GuiTexture(loader->loadTexture("gui/green")->getId(), glm::vec2(-0.7f, 0.9f),
                                       glm::vec2(0.185f, 0.070f));
    auto *guiHeart2 = new GuiTexture(loader->loadTexture("gui/heart")->getId(), glm::vec2(-0.9f, 0.9f),
                                     glm::vec2(0.075f, 0.075f));

    auto sampleModifiedGui = new GuiTexture(loader->loadTexture("gui/lifebar")->getId(), glm::vec2(-0.72f, 0.3f),
                                            glm::vec2(0.290f, 0.0900f) / 3.0f);


    std::vector<GuiRect *> rects = std::vector<GuiRect *>();
    glm::vec3 color = glm::vec3(ColorName::Whitesmoke.getR(), ColorName::Whitesmoke.getG(),
                                ColorName::Whitesmoke.getB());
    glm::vec2 position = glm::vec2(-0.75f, 0.67f);
    glm::vec2 size = glm::vec2(0.290f, 0.0900f);
    glm::vec2 scale = glm::vec2(0.275f, 0.270f);
    float alpha = 0.66f;

    auto *guiRect = new GuiRect(color, position, size, scale, alpha);
    glm::vec2 position2 = glm::vec2(-0.55f, 0.37f);
    glm::vec3 color2 = glm::vec3(ColorName::Green.getR(), ColorName::Green.getG(),
                                 ColorName::Green.getB());
    auto *guiRect2 = new GuiRect(color2, position2, size, scale, alpha);
    rects.push_back(guiRect);

    sampleModifiedGui->addChild(sampleModifiedGui, new UiConstraints(new UiPercentConstraint(XAxis, 0.0f),
                                                                     new UiPercentConstraint(YAxis, 0.0f), 200, 200));

    /**
    * Font Configuration
    */
    // Initialize Texting
    TextMaster::init(loader);

    const std::string &ARIAL = "arial";
    const std::string &NOODLE = "noodle";

    FontType arialFont = TextMeshData::loadFont(ARIAL, 48);
    FontType noodleFont = TextMeshData::loadFont(NOODLE, 48);


    FontModel *fontLoaded = loader->loadFontVAO();
    auto *text1 = new GUIText(
            "This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. This is a sample of a mutliline text. ",
            0.50f, fontLoaded, &noodleFont, glm::vec2(25.0f, 225.0f), ColorName::Whitesmoke,
            0.50f * static_cast<float>(DisplayManager::Width()),
            false);
    auto *text2 = new GUIText("Joseph Alai MCMXII", 0.5f, fontLoaded, &arialFont, glm::vec2(540.0f, 50.0f),
                              ColorName::Cyan,
                              0.75f * static_cast<float>(DisplayManager::Width()), false);
    GUIText *text3 = text2;
    auto clickColorText = new GUIText("Color: ", 0.5f, fontLoaded, &arialFont, glm::vec2(10.0f, 20.0f),
                                      ColorName::Whitesmoke,
                                      0.75f * static_cast<float>(DisplayManager::Width()), false);


    GuiComponent *masterContainer = UiMaster::getMasterComponent();

    auto *parent = new GuiComponent(Container::CONTAINER, new UiConstraints(new UiPercentConstraint(XAxis, 0.01f),
                                                                            new UiPercentConstraint(YAxis, -0.01f), 50,
                                                                            50));
    parent->setName("Parent");
    masterContainer->setName("Master Container");

    guiHeart1->setName("gui/lifebar");
    guiGreenBar->setName("gui/green");
    guiHeart2->setName("gui/heart");

    masterContainer->addChild(guiRect, new UiConstraints(new UiPercentConstraint(XAxis, 0.70f),
                                                         new UiPercentConstraint(YAxis, -0.9f), 50, 50));
    masterContainer->addChild(guiRect2, new UiConstraints(new UiPercentConstraint(XAxis, 0.50f),
                                                          new UiPercentConstraint(YAxis, -0.4f), 50, 50));
    masterContainer->addChild(parent, new UiConstraints(new UiPercentConstraint(XAxis, 0.102f),
                                                        new UiPercentConstraint(YAxis, -0.5f), 50, 50));

    parent->addChild(guiHeart1,
                     new UiConstraints(new UiPercentConstraint(XAxis, 0.033f), new UiPercentConstraint(YAxis, -0.2f),
                                       50, 50));
    parent->addChild(guiGreenBar,
                     new UiConstraints(new UiPixelConstraint(XAxis, -600), new UiPixelConstraint(YAxis, 300),
                                       50, 50));
    parent->addChild(guiHeart2,
                     new UiConstraints(new UiPercentConstraint(XAxis, 0.001f), new UiPercentConstraint(YAxis, -0.3f),
                                       50, 50));
    parent->addChild(text1,
                     new UiConstraints(new UiPercentConstraint(XAxis, 0.00f), new UiPercentConstraint(YAxis, .7), 50,
                                       50));
    parent->addChild(text2,
                     new UiConstraints(new UiPercentConstraint(XAxis, 0.00f), new UiPercentConstraint(YAxis, .7), 50,
                                       50));


    parent->addChild(clickColorText,
                     new UiConstraints(new UiPercentConstraint(XAxis, 0.00f), new UiPercentConstraint(YAxis, 00.1f), 50,
                                       50));
    guiHeart1->addChild(text3,
                        new UiConstraints(new UiPercentConstraint(XAxis, 0.0f), new UiPercentConstraint(YAxis, 0.0f),
                                          50,
                                          50));

    guiRect->setName("GuiRect");
    guiRect2->setName("GuiRect2");

    masterContainer->initialize();

    UiMaster::applyConstraints(masterContainer);
    UiMaster::createRenderQueue(masterContainer);

    /**
     * Framebuffers
     */
    auto reflectFbo = new FrameBuffers();
    auto gui = new GuiTexture(reflectFbo->getReflectionTexture(), glm::vec2(0.75f, 0.75f), glm::vec2(0.2f));
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

    allBoxes.reserve(entities.size());
    allBoxes.insert(allBoxes.end(), entities.begin(), entities.end());

    /**
     * Main Game Loop
     */
    int sin = 0;
    while (DisplayManager::stayOpen()) {
        playerCamera->move(terrain);
        picker->update();

        /*
         * After the user has clicked, render the bounding boxes off-screen, and grab the pixel color of where their
         * mouse is. This color is the Hash ID generated which points to a specific object. So it returns the object.
         */
        if (InputMaster::hasPendingClick()) {
            if (InputMaster::mouseClicked(LeftClick)) {
                renderer->renderBoundingBoxes(allBoxes);
                Color clickColor = Picker::getColor();
                int element = BoundingBoxIndex::getIndexByColor(clickColor);
                Interactive *pClickedModel = InteractiveModel::getInteractiveBox(
                        BoundingBoxIndex::getIndexByColor(clickColor));
                if (pClickedModel != nullptr) {
                    if (auto a = dynamic_cast<Player *>(pClickedModel)) {
                        if (!a->hasMaterial()) {
                            a->setMaterial({500.0f, 500.0f});
                            a->activateMaterial();
                        } else {
                            a->disableMaterial();
                        }
                    }
                    printf("position: x, y, z: (%f, %f, %f)\n", pClickedModel->getPosition().x,
                           pClickedModel->getPosition().y, pClickedModel->getPosition().z);
                }
                const string &renderString =
                        ColorName::toString(clickColor) + ", Element: " + std::to_string(element);
                *clickColorText = GUIText(renderString,
                                          0.5f, fontLoaded, &noodleFont,
                                          glm::vec2(InputMaster::mouseX, InputMaster::mouseY), clickColor,
                                          0.75f * static_cast<float>(DisplayManager::Width()), false);
                InputMaster::resetClick();
            }
        }

        sampleModifiedGui->getPosition() += glm::vec2(0.001f, 0.001f);

        // framebuffer only
        reflectFbo->bindReflectionFrameBuffer();
        {
            renderer->renderBoundingBoxes(allBoxes);
        }
        reflectFbo->unbindCurrentFrameBuffer();

        // non framebuffer
        renderer->renderScene(entities, std::vector<AssimpEntity *>(), allTerrains, lights);
        text3->getPosition() += glm::vec2(.1f);

        // moves everything to the right
        UiMaster::getMasterComponent()->constraints->position += glm::vec2(0.001f, 0.0f);
        UiMaster::applyConstraints(masterContainer);

        parent->constraints->position += glm::vec2(0.00f, 0.002f);
        UiMaster::applyConstraints(parent);

        guiHeart1->constraints->position += glm::vec2(0.00f, -0.001f);
        UiMaster::applyConstraints(guiHeart1);

        guiGreenBar->constraints->position += glm::vec2(0.00f, -0.005f);
        guiGreenBar->addChild(text1, text1->getConstraints());
        UiMaster::applyConstraints(guiRect);


        UiMaster::render();

        DisplayManager::updateDisplay();
    }

    /**
     * Clean up renderers and loaders
     */
    reflectFbo->cleanUp();
    TextMaster::cleanUp();
    fontRenderer->cleanUp();
    guiRenderer->cleanUp();
    rectRenderer->cleanUp();
    renderer->cleanUp();
    loader->cleanUp();

    /**
     * Close display
     */
    DisplayManager::closeDisplay();
}
