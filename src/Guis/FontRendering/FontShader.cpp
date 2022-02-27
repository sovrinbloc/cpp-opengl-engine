//
// Created by Joseph Alai on 7/22/21.
//

#include "FontShader.h"

FontShader::FontShader()
        : ShaderProgram(VertexPath, FragmentPath, nullptr) {
    this->initialize();
    this->loadProjectionMatrix();
}

void FontShader::bindAttributes() {
    this->bindAttribute(0, vertex);
}

void FontShader::loadProjectionMatrix(glm::mat4 matrix) {
    this->setMat4(location_projectionMatrix, matrix);
}

void FontShader::loadTextColor(Color color) {
    this->setVec3(location_textColor, color.getColorRGB());
}

void FontShader::getAllUniformLocations() {
    location_textColor = getUniformLocation(textColor);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
}