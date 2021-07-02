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

using namespace glm;

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();

        auto *shader = new StaticShader();
        Loader loader = Loader();
        Renderer renderer = Renderer();

        std::vector<GLfloat> vertices = {
                -0.5f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
        };

        std::vector<GLint> indices{
                0, 1, 3,
                3, 1, 2
        };

        std::vector<GLfloat> textureCoords = {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
        };

        RawModel *model = loader.loadToVAO(vertices, textureCoords, indices);

        auto *texture = new ModelTexture(FileSystem::Path("/res/image.png"), PNG);

        auto *staticModel = new TexturedModel(model, texture);

        auto *entity = new Entity(staticModel, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0), 1);

        while (DisplayManager::stayOpen()) {
            // game logic
            renderer.prepare();
            shader->start();
            renderer.render(entity, shader);
            shader->stop();
            DisplayManager::updateDisplay();
        }

        shader->cleanUp();
        loader.cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
