//
// Created by Joseph Alai on 7/25/21.
//

#include "BoundingBoxShader.h"


BoundingBoxShader::BoundingBoxShader() : ShaderProgram(VertexPath, FragmentPath, nullptr) {
    this->initialize();
    this->loadTransformationMatrix();
}

void BoundingBoxShader::bindAttributes() {
    this->bindAttribute(0, position);
}

void BoundingBoxShader::loadTransformationMatrix(glm::mat4 matrix) {
    this->setMat4(location_transformationMatrix, matrix);
}

void BoundingBoxShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void BoundingBoxShader::loadViewMatrix(glm::mat4 matrix) {
    this->setMat4(location_viewMatrix, matrix);
}


void BoundingBoxShader::loadBoxColor(glm::vec3 color) {
    this->setVec3(location_boxColor, color);
}

void BoundingBoxShader::loadViewPosition(Camera *camera) {
    this->setVec3(location_viewPosition, camera->Position);
}

void BoundingBoxShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
    location_viewPosition = getUniformLocation(viewPosition);
    location_boxColor = getUniformLocation(boxColor);
}