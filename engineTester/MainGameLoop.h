//
// Created by Joseph Alai on 6/30/21.
//

#ifndef CRAFTPROJ_MAINGAMELOOP_H
#define CRAFTPROJ_MAINGAMELOOP_H

#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"
#include "../shaders/ShaderProgram.h"

class MainGameLoop {
public:
    static void main() {
        DisplayManager::createDisplay();
        Loader loader = Loader();
        Renderer renderer = Renderer();
        ShaderProgram shader = ShaderProgram(
                "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/vertex_shader.glsl",
                "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/fragment_shader.glsl");


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
