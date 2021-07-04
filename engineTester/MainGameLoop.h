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

using namespace glm;

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();

        StaticShader *shader;
        Loader *loader;
        Renderer *renderer;
        Camera *viewCamera;
        CameraInput *cameraInput;

        shader = new StaticShader();
        loader = new Loader();
        renderer = new Renderer(shader);
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

        while (DisplayManager::stayOpen()) {
            // game logic
            entity->rotate(glm::vec3(0.0f, 0.1f, 0.0f));
            renderer->prepare();
            shader->start();
            shader->loadLight(light);
            renderer->render(cameraInput, entity, shader);
            shader->stop();
            DisplayManager::updateDisplay();
        }

        shader->cleanUp();
        loader->cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
