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

        renderer = new Renderer(DisplayManager::getWidth(), DisplayManager::getHeight());

        viewCamera = new Camera();

        cameraInput = new CameraInput(viewCamera);

        std::vector<GLfloat> vertices = {
                -0.5f,0.5f,-0.5f,
                -0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,-0.5f,
                0.5f,0.5f,-0.5f,

                -0.5f,0.5f,0.5f,
                -0.5f,-0.5f,0.5f,
                0.5f,-0.5f,0.5f,
                0.5f,0.5f,0.5f,

                0.5f,0.5f,-0.5f,
                0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,0.5f,
                0.5f,0.5f,0.5f,

                -0.5f,0.5f,-0.5f,
                -0.5f,-0.5f,-0.5f,
                -0.5f,-0.5f,0.5f,
                -0.5f,0.5f,0.5f,

                -0.5f,0.5f,0.5f,
                -0.5f,0.5f,-0.5f,
                0.5f,0.5f,-0.5f,
                0.5f,0.5f,0.5f,

                -0.5f,-0.5f,0.5f,
                -0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,-0.5f,
                0.5f,-0.5f,0.5f
        };

        std::vector<GLint> indices{
                0,1,3,
                3,1,2,
                4,5,7,
                7,5,6,
                8,9,11,
                11,9,10,
                12,13,15,
                15,13,14,
                16,17,19,
                19,17,18,
                20,21,23,
                23,21,22
        };

        std::vector<GLfloat> textureCoords = {
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0,
                0,0,
                0,1,
                1,1,
                1,0
        };

        RawModel *model;
        ModelTexture *texture;
        TexturedModel *staticModel;
        Entity *entity;

        model = loader->loadToVAO(vertices, textureCoords, indices);

        texture = new ModelTexture(FileSystem::Path("/res/image.png"), PNG);

        staticModel = new TexturedModel(model, texture);

        entity = new Entity(staticModel, glm::vec3(-0.50f, 0.0f, 0.0f), glm::vec3(0), 1);

        while (DisplayManager::stayOpen()) {
            // game logic
            entity->increasePosition(glm::vec3(0.0f, 0.0f, -0.01f));
            renderer->prepare();
            shader->start();
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
