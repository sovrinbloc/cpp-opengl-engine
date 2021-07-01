//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../renderEngine/Shader.h"

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();
        Loader loader = Loader();
        Renderer renderer = Renderer();
        Shader shader = Shader(
                "/Users/josephalai/Projects/games/cpp-mc/engine/renderEngine/shaders/vertex_shader.glsl",
                "/Users/josephalai/Projects/games/cpp-mc/engine/renderEngine/shaders/fragment_shader.glsl");


        float vertices[] = {
                -0.5f, 0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };

        RawModel model = loader.loadToVAO(vertices);

        while (DisplayManager::stayOpen()) {
            // game logic
            renderer.prepare();
            shader.use();
            renderer.render(model);
            DisplayManager::updateDisplay();
        }

        loader.cleanUp();
        DisplayManager::closeDisplay();
    }
};

#endif //CRAFTPROJ_MAINGAMELOOP_H
