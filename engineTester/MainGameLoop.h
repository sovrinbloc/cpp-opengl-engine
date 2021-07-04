//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../toolbox/FileSystem.h"
#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
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
        StaticShader *shader;

        loader = new Loader();
        viewCamera = new Camera();
        cameraInput = new CameraInput(viewCamera);

        RawModel *model;
        ModelTexture *texture;
        TexturedModel *staticModel;
        Entity *entity;
        Light *light;

        light = new Light(glm::vec3(0.0, 0.0, -20), glm::vec3(1, 1, 1));
        model = OBJLoader::loadObjModel("/res/stall/stall.obj", loader);
        texture = new ModelTexture(FileSystem::Path("/res/stall/stallTexture.png"), PNG);
        staticModel = new TexturedModel(model, texture);

        texture->setShineDamper(10);
        texture->setReflectivity(0.5f);
        texture->setAmbient(0.1);


        entity = new Entity(staticModel, glm::vec3(-0.50f, 0.0f, 0.0f), glm::vec3(0), 0.1);

        std::vector<Entity *> allEntities;

        for (int i = 0; i < 200; ++i) {
            float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100 - 50;
            float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 100 - 50;
            float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * -300;

            float rx, ry, rz, scale;
            rx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            ry = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            rz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            glm::vec3 rot(rx, ry, rz);
            rot = rot * 180.0f;
            scale = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            allEntities.push_back(new Entity(staticModel, glm::vec3(x, y, z), rot, scale));
        }


        MasterRenderer *renderer;
        renderer = new MasterRenderer();
        while (DisplayManager::stayOpen()) {
            // game logic
            for (Entity *booth : allEntities) {
                renderer->processEntity(booth);
            }
            renderer->render(light, cameraInput);
            DisplayManager::updateDisplay();
        }

        renderer->cleanUp();
        loader->cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
