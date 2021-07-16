//
// Created by Joseph Alai on 7/6/21.
//

#include "StaticShader.h"

static const char *VertexPath = "/src/Shaders/Static/VertexShader.glsl";
static const char *FragmentPath = "/src/Shaders/Static/FragmentShader.glsl";

StaticShader::StaticShader() : ShaderProgram(VertexPath, FragmentPath, nullptr) {
    this->initialize();
    this->loadTransformationMatrix();
}

void StaticShader::bindAttributes() {
    this->bindAttribute(0, position);
    this->bindAttribute(1, texture);
    this->bindAttribute(2, normal);
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix) {
    this->setMat4(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(glm::mat4 matrix) {
    this->setMat4(location_viewMatrix, matrix);
}

void StaticShader::loadViewPosition(Camera *camera) {
    this->setVec3(location_viewPosition, camera->Position);
}

void StaticShader::loadLight(Light *light) {
    this->setVec3(location_lightPosition, light->getPosition());
    this->setVec3(location_lightColor, light->getColor());

    // for textures and lighting
    this->setVec3(location_lightAmbient, light->getLighting().ambient);
    this->setVec3(location_lightDiffuse, light->getLighting().diffuse);
    this->setVec3(location_lightSpecular, light->getLighting().specular);
    this->setVec3(location_lightPosition, light->getLighting().position);
}

void StaticShader::loadMaterial(Material material) {
    this->setFloat(location_materialShininess, material.shininess);
    this->setVec3(location_materialAmbient, material.ambient);
    this->setVec3(location_materialDiffuse, material.diffuse);
    this->setVec3(location_materialSpecular, material.specular);
}

void StaticShader::loadFakeLightingVariable(bool useFakeLighting) {
    this->setBool(location_useFakeLighting, useFakeLighting);
}

void StaticShader::loadSkyColorVariable(glm::vec3 skyColor) {
    this->setVec3(location_skyColor, skyColor);
}

void StaticShader::loadNumberOfRows(int rows) {
    this->setFloat(location_textureNumberOfRows, (float)rows);
}

void StaticShader::loadOffset(float x, float y) {
    this->setVec2(location_textureOffset, glm::vec2(x, y));
}


void StaticShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
    location_lightColor = getUniformLocation(lightColor);
    location_useFakeLighting = getUniformLocation(useFakeLighting);
    location_skyColor = getUniformLocation(skyColor);
    location_viewPosition = getUniformLocation(viewPosition);

    location_textureNumberOfRows = getUniformLocation(textureNumberOfRows);
    location_textureOffset = getUniformLocation(textureOffset);

// for textures and lighting
    location_lightAmbient = getUniformLocation(lightAmbient);
    location_lightDiffuse = getUniformLocation(lightDiffuse);
    location_lightSpecular = getUniformLocation(lightSpecular);
    location_lightPosition = getUniformLocation(lightPosition);

    location_materialShininess = getUniformLocation(materialShininess);
    location_materialAmbient = getUniformLocation(materialAmbient);
    location_materialDiffuse = getUniformLocation(materialDiffuse);
    location_materialSpecular = getUniformLocation(materialSpecular);

}