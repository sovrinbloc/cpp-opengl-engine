//
// Created by Joseph Alai on 7/8/21.
//

#include "ModelShader.h"


static const char *VertexPath = "/src/Shaders/Scene/VertexShader.glsl";
static const char *FragmentPath = "/src/Shaders/Scene/FragmentShader.glsl";

ModelShader::ModelShader() : ShaderProgram(VertexPath, FragmentPath, nullptr) {
    this->initialize();
    this->loadTransformationMatrix();
}

void ModelShader::bindAttributes() {
    this->bindAttribute(0, position);
    this->bindAttribute(1, texture);
    this->bindAttribute(2, normal);
}

void ModelShader::loadTransformationMatrix(glm::mat4 matrix) {
    this->setMat4(location_transformationMatrix, matrix);
}

void ModelShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void ModelShader::loadViewMatrix(glm::mat4 matrix) {
    this->setMat4(location_viewMatrix, matrix);
}

void ModelShader::loadViewPosition(Camera *camera) {
    this->setVec3(location_viewPosition, camera->Position);
}

void ModelShader::loadLight(Light *light) {
    this->setVec3(location_lightPosition, light->getPosition());
    this->setVec3(location_lightColor, light->getColor());

    // for textures and lighting
    this->setVec3(location_lightAmbient, light->getLighting().ambient);
    this->setVec3(location_lightDiffuse, light->getLighting().diffuse);
    this->setVec3(location_lightSpecular, light->getLighting().specular);
    this->setVec3(location_lightPosition, light->getLighting().position);
}

void ModelShader::loadMaterial(Material material) {
    this->setFloat(location_materialShininess, material.shininess);
    this->setVec3(location_materialAmbient, material.ambient);
    this->setVec3(location_materialDiffuse, material.diffuse);
    this->setVec3(location_materialSpecular, material.specular);
}

void ModelShader::loadSkyColorVariable(glm::vec3 skyColor) {
    this->setVec3(location_skyColor, skyColor);
}


void ModelShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
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

}