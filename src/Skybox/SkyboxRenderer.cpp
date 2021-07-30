//
// Created by Joseph Alai on 7/20/21.
//

#include "SkyboxRenderer.h"
#include "../Util/Colors.h"


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
    std::vector<std::string> initDayTextureFiles() {
        return {
                FileSystem::Skybox("clouds/right"),
                FileSystem::Skybox("clouds/left"),
                FileSystem::Skybox("clouds/top"),
                FileSystem::Skybox("clouds/bottom"),
                FileSystem::Skybox("clouds/back"),
                FileSystem::Skybox("clouds/front")
        };
    }
    std::vector<std::string> initNightTextureFiles() {
        return {
                FileSystem::Skybox("stars/right"),
                FileSystem::Skybox("stars/left"),
                FileSystem::Skybox("stars/top"),
                FileSystem::Skybox("stars/bottom"),
                FileSystem::Skybox("stars/back"),
                FileSystem::Skybox("stars/front")
        };
    }
}

SkyboxRenderer::SkyboxRenderer(Loader *loader, glm::mat4 projectionMatrix, glm::vec3 *skyColor)  : sBoxVertices(initVertices(sBoxSize)), sTextureFiles(
        initDayTextureFiles()), sNightTextureFiles(initNightTextureFiles()), skyColor(skyColor)  {
    cube = loader->loadToVAO(sBoxVertices, 3);
    dayTextureId = loader->loadCubeMap(sTextureFiles);
    nightTextureId = loader->loadCubeMap(sNightTextureFiles);
    shader = new SkyboxShader();
    shader->start();
    shader->connectTextureUnits();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->stop();
}

void SkyboxRenderer::render(Camera *camera) {
    glDepthMask(GL_FALSE);
    shader->start();
    glm::mat4 view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    shader->loadViewMatrix(view);
    shader->loadFogColor(*skyColor);
    glBindVertexArray(cube->getVaoId());
    glEnableVertexAttribArray(0);
    bindTextures();
    glDrawArrays(GL_TRIANGLES, 0, cube->getVertexCount());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader->stop();
    glDepthMask(GL_TRUE);
}

void SkyboxRenderer::bindTextures() {
    time += DisplayManager::getFrameTimeSeconds() * 1000;
    time = (float)(static_cast<int>(time) % 24000);
    unsigned int texture1;
    unsigned int texture2;
    float blendFactor;
    if(time >= 0 && time < 5000){
        texture1 = nightTextureId;
        texture2 = nightTextureId;
        *skyColor = Colors::Skyblue;
        blendFactor = (time - 0)/(5000 - 0);
    }else if(time >= 5000 && time < 8000){
        texture1 = nightTextureId;
        texture2 = dayTextureId;
        blendFactor = (time - 5000)/(8000 - 5000);
        *skyColor = Colors::Lightgrey;
    }else if(time >= 8000 && time < 21000){
        texture1 = dayTextureId;
        texture2 = dayTextureId;
        *skyColor = Colors::Whitesmoke;
        blendFactor = (time - 8000)/(21000 - 8000);
    }else{
        texture1 = dayTextureId;
        texture2 = nightTextureId;
        *skyColor = Colors::Black;
        blendFactor = (time - 21000)/(24000 - 21000);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture2);
    shader->loadBlendFactor(blendFactor);
}



