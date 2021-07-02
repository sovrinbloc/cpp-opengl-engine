//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../libraries/utils/filesystem.h"
#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"
#include "../textures/ModelTexture.h"
#include "../models/TexturedModel.h"

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();

        StaticShader shader = StaticShader();
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
        auto *texturedModel = new TexturedModel(model, texture);

        while (DisplayManager::stayOpen()) {
            // game logic
            renderer.prepare();
            shader.start();
            renderer.render(texturedModel);
            shader.stop();
            DisplayManager::updateDisplay();
        }

        shader.cleanUp();
        loader.cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
