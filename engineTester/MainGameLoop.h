//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../toolbox/FileSystem.h"
#include "../toolbox/Utils.h"
#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/EntityRenderer.h"
#include "../shaders/StaticShader.h"
#include "../textures/ModelTexture.h"
#include "../models/TexturedModel.h"
#include "../toolbox/Maths.h"
#include "../entities/CameraInput.h"
#include "../renderEngine/ObjLoader.h"
#include "../renderEngine/MasterRenderer.h"

using namespace glm;

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();

        Loader *loader;
        Camera *viewCamera;
        CameraInput *cameraInput;

        loader = new Loader();
        viewCamera = new Camera(glm::vec3(0.0f, 4.5f, 0.0f));
        cameraInput = new CameraInput(viewCamera);

        RawModel *grassModel, *treeModel;
        ModelTexture *grassTexture, *treeTexture;
        TexturedModel *staticGrass, *staticTree;
        Light *light;

        light = new Light(glm::vec3(0.0, 124.0, -20), glm::vec3(1, 1, 1));

        grassModel = OBJLoader::loadObjModel("/res/tut/grassModel.obj", loader);
        grassTexture = new ModelTexture(FileSystem::Path("/res/tut/grassTexture.png"), PNG);
        staticGrass = new TexturedModel(grassModel, grassTexture);
        grassTexture->setHasTransparency(true);
//        grassTexture->setUseFakeLighting(true);

        treeModel = OBJLoader::loadObjModel("/res/tut/lowPolyTree.obj", loader);
        treeTexture = new ModelTexture(FileSystem::Path("/res/tut/lowPolyTree.png"), PNG);
        staticTree = new TexturedModel(treeModel, treeTexture);

        grassTexture->setShineDamper(10);
        grassTexture->setReflectivity(0.5f);
        grassTexture->setAmbient(0.1);

        treeTexture->setShineDamper(100);
        treeTexture->setReflectivity(0.1f);
        treeTexture->setAmbient(0.1);

        std::vector<Entity *> allEntities;

        for (int i = 0; i < 50; ++i) {
            float x = randomFloat() * 100 - 50;
            float y = randomFloat() * 0;
            float z = randomFloat() * -300;

            float rx, ry, rz, scale;
            rx = 0;
            ry = 0;
            rz = 0;
            glm::vec3 rot(rx, ry, rz);
            rot = rot * 180.0f;
            allEntities.push_back(new Entity(staticGrass, glm::vec3(x, y, z), rot));
            allEntities.push_back(new Entity(staticTree, glm::vec3(x * 1.5, y, z * 1.5), rot, randomFloat()));
        }

        Terrain *terrain, *terrain2;
        terrain = new Terrain(-1, -1, loader, new ModelTexture(FileSystem::Path("/res/grass.png"), PNG));
        terrain2 = new Terrain(0, -1, loader, new ModelTexture(FileSystem::Path("/res/grass.png"), PNG));



        MasterRenderer *renderer;
        renderer = new MasterRenderer(cameraInput);
        while (DisplayManager::stayOpen()) {
            // game logic
            renderer->processTerrain(terrain);
            renderer->processTerrain(terrain2);
            for (Entity *booth : allEntities) {
                renderer->processEntity(booth);
            }
            renderer->render(light);
            DisplayManager::updateDisplay();
        }

        renderer->cleanUp();
        loader->cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
