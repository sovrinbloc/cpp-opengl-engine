//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/StaticShader.h"

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();
        Loader loader = Loader();
        Renderer renderer = Renderer();
        StaticShader shader = StaticShader();


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

        RawModel model = loader.loadToVAO(vertices, indices);

        while (DisplayManager::stayOpen()) {
            // game logic
            renderer.prepare();
            shader.use();
            renderer.render(model);
            shader.stop();
            DisplayManager::updateDisplay();
        }

        loader.cleanUp();
        shader.cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
