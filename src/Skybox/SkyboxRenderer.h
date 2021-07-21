//
// Created by Joseph Alai on 7/20/21.
//

#ifndef ENGINE_SKYBOXRENDERER_H
#define ENGINE_SKYBOXRENDERER_H

#include <vector>
#include "iostream"
#include "../Models/RawModel.h"
#include "SkyboxShader.h"

namespace {
    std::vector<float> initVertices(float SIZE) {
        return std::vector<float>{
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
    }
    std::vector<std::string> initTextureFiles() {
        return {
                FileSystem::Skybox("right"),
                FileSystem::Skybox("left"),
                FileSystem::Skybox("top"),
                FileSystem::Skybox("bottom"),
                FileSystem::Skybox("back"),
                FileSystem::Skybox("front")
        };
    }
}

class SkyboxRenderer {

private:
    const float sBoxSize = 500.0f;
    const std::vector<float> sBoxVertices;

    const std::vector<std::string> sTextureFiles;

    RawModel *cube;
    unsigned int textureId;
    SkyboxShader *shader;

public:
    SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix);

    void render(Camera *camera, glm::vec3 color);
};


#endif //ENGINE_SKYBOXRENDERER_H
