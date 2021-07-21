//
// Created by Joseph Alai on 7/20/21.
//

#include "SkyboxShader.h"

static const char *VertexPath = "/src/Skybox/VertexShader.glsl";
static const char *FragmentPath = "/src/Skybox/FragmentShader.glsl";

SkyboxShader::SkyboxShader() : ShaderProgram (VertexPath, FragmentPath) {
    this->initialize();
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(glm::mat4 matrix) {
    this->setMat4(location_viewMatrix, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 color) {
    this->setVec3(location_fogColor, color);
}

void SkyboxShader::getAllUniformLocations() {
    location_projectionMatrix = this->getUniformLocation("projectionMatrix");
    location_viewMatrix = this->getUniformLocation("viewMatrix");
    location_fogColor = this->getUniformLocation("fogColor");
}

void SkyboxShader::bindAttributes() {
    this->bindAttribute(0, "position");
}
