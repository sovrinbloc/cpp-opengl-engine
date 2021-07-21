//
// Created by Joseph Alai on 7/6/21.
//

#include "StaticShader.h"
#include "../Toolbox/Utils.h"

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

void StaticShader::loadLight(std::vector<Light *>lights) {

    // for textures and lighting
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if (i < lights.size()) {
            this->setFloat(location_lightConstant[i], lights[i]->getLighting().constant);
            this->setFloat(location_lightLinear[i], lights[i]->getLighting().linear);
            this->setFloat(location_lightQuadratic[i], lights[i]->getLighting().quadratic);

            this->setVec3(location_lightAmbient[i], lights[i]->getLighting().ambient);
            this->setVec3(location_lightDiffuse[i], lights[i]->getLighting().diffuse);
            this->setVec3(location_lightSpecular[i], lights[i]->getColor());
            this->setVec3(location_lightPosition[i], lights[i]->getPosition());
        } else {
            this->setFloat(location_lightConstant[i], 0.0f);
            this->setFloat(location_lightLinear[i], 0.0f);
            this->setFloat(location_lightQuadratic[i], 0.0f);

            this->setVec3(location_lightAmbient[i], glm::vec3(0.0f));
            this->setVec3(location_lightDiffuse[i], glm::vec3(0.0f));
            this->setVec3(location_lightSpecular[i], glm::vec3(0.0f));
            this->setVec3(location_lightPosition[i], glm::vec3(0.0f));
        }
    }
}

void StaticShader::loadMaterial(Material material) {
    this->setFloat(location_materialShininess, material.shininess);
    this->setFloat(location_materialReflectivity, material.reflectivity);
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
    location_useFakeLighting = getUniformLocation(useFakeLighting);
    location_skyColor = getUniformLocation(skyColor);
    location_viewPosition = getUniformLocation(viewPosition);

    location_textureNumberOfRows = getUniformLocation(textureNumberOfRows);
    location_textureOffset = getUniformLocation(textureOffset);

    // for textures and lighting
    for(int i = 0; i < MAX_LIGHTS; i++) {
        location_lightPosition[i] = getUniformLocation(Utils::shaderArray(light, i, lightPosition));

        location_lightDiffuse[i] = getUniformLocation(Utils::shaderArray(light, i, lightDiffuse));
        location_lightAmbient[i] = getUniformLocation(Utils::shaderArray(light, i, lightAmbient));
        location_lightSpecular[i] = getUniformLocation(Utils::shaderArray(light, i, lightSpecular));

        location_lightConstant[i] = getUniformLocation(Utils::shaderArray(light, i, lightConstant));
        location_lightLinear[i] = getUniformLocation(Utils::shaderArray(light, i, lightLinear));
        location_lightQuadratic[i] = getUniformLocation(Utils::shaderArray(light, i, lightQuadratic));
    }

    location_materialShininess = getUniformLocation(materialShininess);
    location_materialReflectivity = getUniformLocation(materialReflectivity);

}