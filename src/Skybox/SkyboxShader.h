//
// Created by Joseph Alai on 7/20/21.
//

#ifndef ENGINE_SKYBOXSHADER_H
#define ENGINE_SKYBOXSHADER_H


#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"
#include "glm/glm.hpp"

class SkyboxShader : public ShaderProgram {
private:
    constexpr static const char *VertexPath = "/src/Skybox/VertexShader.glsl";
    constexpr static const char *FragmentPath = "/src/Skybox/FragmentShader.glsl";

    int location_projectionMatrix;
    int location_viewMatrix;
    int location_fogColor;
    int location_blendFactor;
    int location_cubeMap;
    int location_cubeMap2;

    constexpr static float kRotationSpeed = 1.0f;
    float rotation = 0.0f;

public:
    SkyboxShader();

    void loadProjectionMatrix(glm::mat4 matrix);

    void loadViewMatrix(glm::mat4 matrix);

    void loadFogColor(Color color);

    void loadBlendFactor(float blend);

    void connectTextureUnits();

protected:
    void getAllUniformLocations() override;

    void bindAttributes() override;
};


#endif //ENGINE_SKYBOXSHADER_H
