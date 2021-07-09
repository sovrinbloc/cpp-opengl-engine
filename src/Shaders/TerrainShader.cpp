//
// Created by Joseph Alai on 7/6/21.
//

#include "TerrainShader.h"

static const char *VertexPath = "/src/Shaders/Terrain/VertexShader.glsl";
static const char *FragmentPath = "/src/Shaders/Terrain/FragmentShader.glsl";

TerrainShader::TerrainShader() : ShaderProgram(VertexPath, FragmentPath, nullptr) {
    this->initialize();
    this->loadTransformationMatrix();
}

void TerrainShader::bindAttributes() {
    this->bindAttribute(0, position);
    this->bindAttribute(1, texture);
    this->bindAttribute(2, normal);
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix) {
    this->setMat4(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(glm::mat4 matrix) {
    this->setMat4(location_viewMatrix, matrix);
}

void TerrainShader::loadLight(Light *light) {
    this->setVec3(location_lightPosition, light->getPosition());
    this->setVec3(location_lightColor, light->getColor());

    // for textures and lighting
    this->setVec3(location_lightAmbient, light->getLighting().ambient);
    this->setVec3(location_lightDiffuse, light->getLighting().diffuse);
    this->setVec3(location_lightSpecular, light->getLighting().specular);
    this->setVec3(location_lightPosition, light->getLighting().position);
}

void TerrainShader::loadMaterial(Material material) {
    this->setFloat(location_materialShininess, material.shininess);
    this->setVec3(location_materialAmbient, material.ambient);
    this->setVec3(location_materialDiffuse, material.diffuse);
    this->setVec3(location_materialSpecular, material.specular);
}

void TerrainShader::loadSkyColorVariable(glm::vec3 skyColor) {
    this->setVec3(location_skyColor, skyColor);
}

void TerrainShader::loadViewPosition(Camera *camera) {
    this->setVec3(location_viewPosition, camera->Position);
}

void TerrainShader::connectTextureUnits() {
    this->setInt(location_backgroundTexture, 0);
    this->setInt(location_rTexture, 1);
    this->setInt(location_gTexture, 2);
    this->setInt(location_bTexture, 3);
    this->setInt(location_blendMap, 4);
}

void TerrainShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
    location_lightPosition = getUniformLocation(lightPosition);
    location_lightColor = getUniformLocation(lightColor);
    location_skyColor = getUniformLocation(skyColor);

    location_viewPosition = getUniformLocation(viewPosition);

// for textures and lighting
    location_lightAmbient = getUniformLocation(lightAmbient);
    location_lightDiffuse = getUniformLocation(lightDiffuse);
    location_lightSpecular = getUniformLocation(lightSpecular);
    location_lightPosition = getUniformLocation(lightPosition);

    location_materialShininess = getUniformLocation(materialShininess);
    location_materialAmbient = getUniformLocation(materialAmbient);
    location_materialDiffuse = getUniformLocation(materialDiffuse);
    location_materialSpecular = getUniformLocation(materialSpecular);

    location_backgroundTexture = getUniformLocation(backgroundTexture);
    location_rTexture = getUniformLocation(rTexture);
    location_gTexture = getUniformLocation(gTexture);
    location_bTexture = getUniformLocation(bTexture);
    location_blendMap = getUniformLocation(blendMap);
}