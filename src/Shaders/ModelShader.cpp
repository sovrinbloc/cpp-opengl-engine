//
// Created by Joseph Alai on 7/8/21.
//

#include "ModelShader.h"
#include "../Toolbox/Utils.h"


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

void ModelShader::loadLight(std::vector<Light *>lights) {

    // for textures and lighting
    for(int i = 0; i < MAX_LIGHTS; i++) {
        if (i < lights.size()) {
            this->setVec3(location_lightAttenuation[i], lights[i]->getLighting().attenuation);
            this->setVec3(location_lightAmbient[i], lights[i]->getLighting().ambient);
            this->setVec3(location_lightDiffuse[i], lights[i]->getLighting().diffuse);
            this->setVec3(location_lightSpecular[i], lights[i]->getColor());
            this->setVec3(location_lightPosition[i], lights[i]->getPosition());
        } else {
            this->setVec3(location_lightAttenuation[i], glm::vec3(0.0f));
            this->setVec3(location_lightAmbient[i], glm::vec3(0.0f));
            this->setVec3(location_lightDiffuse[i], glm::vec3(0.0f));
            this->setVec3(location_lightSpecular[i], glm::vec3(0.0f));
            this->setVec3(location_lightPosition[i], glm::vec3(0.0f));
        }
    }
}

void ModelShader::loadMaterial(Material material) {
    this->setFloat(location_materialShininess, material.shininess);
    this->setFloat(location_materialReflectivity, material.reflectivity);
}

void ModelShader::loadSkyColorVariable(glm::vec3 skyColor) {
    this->setVec3(location_skyColor, skyColor);
}

void ModelShader::getAllUniformLocations() {
    location_transformationMatrix = getUniformLocation(transformationMatrix);
    location_projectionMatrix = getUniformLocation(projectionMatrix);
    location_viewMatrix = getUniformLocation(viewMatrix);
    location_skyColor = getUniformLocation(skyColor);
    location_viewPosition = getUniformLocation(viewPosition);

    // for textures and lighting
    for(int i = 0; i < MAX_LIGHTS; i++) {
        location_lightAttenuation[i] = getUniformLocation(Utils::shaderArray("light", i, "attenuation"));
        location_lightPosition[i] = getUniformLocation(Utils::shaderArray("light", i, "position"));
        location_lightAmbient[i] = getUniformLocation(Utils::shaderArray("light", i, "ambient"));
        location_lightSpecular[i] = getUniformLocation(Utils::shaderArray("light", i, "specular"));
        location_lightDiffuse[i] = getUniformLocation(Utils::shaderArray("light", i, "diffuse"));
    }

    location_materialShininess = getUniformLocation(materialShininess);
    location_materialReflectivity = getUniformLocation(materialReflectivity);
}