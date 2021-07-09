//
// Created by Joseph Alai on 7/8/21.
//

#include "ModelShader.h"


static const char *VertexPath = "/src/Shaders/Assimp/VertexShader.glsl";
static const char *FragmentPath = "/src/Shaders/Assimp/FragmentShader.glsl";

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


void ModelShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
    location_viewPosition = getUniformLocation(viewPosition);
}