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
    const float sBoxSize = 500.0f;
    const std::vector<float> sBoxVertices;

    const std::vector<std::string> sTextureFiles;
    const std::vector<std::string> sNightTextureFiles;

    float time = 0.0f;

    RawModel *cube;
    unsigned int dayTextureId;
    unsigned int nightTextureId;
    SkyboxShader *shader;
    glm::vec3 *skyColor;

public:
    SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix, glm::vec3 *skyColor);

    void render(Camera *camera);

    void bindTextures();

};


#endif //ENGINE_SKYBOXRENDERER_H
