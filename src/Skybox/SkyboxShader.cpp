//
// Created by Joseph Alai on 7/20/21.
//

#include "SkyboxShader.h"

SkyboxShader::SkyboxShader() : ShaderProgram (VertexPath, FragmentPath) {
    this->initialize();
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewMatrix(glm::mat4 matrix) {
    rotation += kRotationSpeed * DisplayManager::getFrameTimeSeconds();
    matrix = glm::rotate(matrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    this->setMat4(location_viewMatrix, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 color) {
    this->setVec3(location_fogColor, color);
}

void SkyboxShader::getAllUniformLocations() {
    location_projectionMatrix = this->getUniformLocation("projectionMatrix");
    location_viewMatrix = this->getUniformLocation("viewMatrix");
    location_fogColor = this->getUniformLocation("fogColor");
    location_blendFactor = this->getUniformLocation("blendFactor");
    location_cubeMap = this->getUniformLocation("cubeMap");
    location_cubeMap2 = this->getUniformLocation("cubeMap2");
}

void SkyboxShader::bindAttributes() {
    this->bindAttribute(0, "position");
}

void SkyboxShader::loadBlendFactor(float blend) {
    this->setFloat(location_blendFactor, blend);
}

void SkyboxShader::connectTextureUnits() {
    this->setInt(location_cubeMap, 0);
    this->setInt(location_cubeMap2, 1);
}
