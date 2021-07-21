//
// Created by Joseph Alai on 7/20/21.
//

#ifndef ENGINE_SKYBOXRENDERER_H
#define ENGINE_SKYBOXRENDERER_H

#include <vector>
#include "iostream"
#include "../Models/RawModel.h"
#include "SkyboxShader.h"

class SkyboxRenderer {

private:
    constexpr  static float SIZE = 500.0f;
    std::vector<float> VERTICES = {
            -SIZE,  SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,

            -SIZE, -SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,

            -SIZE,  SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE,  SIZE,  SIZE,
            SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE, -SIZE,

            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            SIZE, -SIZE,  SIZE
    };

    std::vector<std::string> TEXTURE_FILES = {
            FileSystem::Skybox("right"),
            FileSystem::Skybox("left"),
            FileSystem::Skybox("top"),
            FileSystem::Skybox("bottom"),
            FileSystem::Skybox("back"),
            FileSystem::Skybox("front")};

    RawModel *cube;
    int texture;
    SkyboxShader *shader;

public:
    SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix);

    void render(Camera *camera, glm::vec3 color);
};


#endif //ENGINE_SKYBOXRENDERER_H
