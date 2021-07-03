//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_STATICSHADER_H
#define ENGINE_STATICSHADER_H

#include "ShaderProgram.h"

static const char *VertexPath = "/shaders/vertex_shader.glsl";
static const char *FragmentPath = "/shaders/fragment_shader.glsl";

class StaticShader : public ShaderProgram {
private:
    const std::string position = "position";
    const std::string texture = "textureCoords";
    const std::string transformationMatrix = "transformationMatrix";
    const std::string projectionMatrix = "projectionMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string lightPosition = "lightPosition";
    const std::string lightColor = "lightColor";
    
    int transformationMatrixLoc;
    int projectionMatrixLoc;
    int viewMatrixLoc;
    int lightPositionLoc;
    int lightColorLoc;
public:
    GLuint attribute;
    StaticShader() : ShaderProgram(VertexPath, FragmentPath,nullptr) {
        this->initialize();
        this->loadTransformationMatrix();
    }

    void bindAttributes() {
        this->bindAttribute(0, position);
        this->bindAttribute(1, texture);
    }

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(transformationMatrixLoc, matrix);
    }

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(projectionMatrixLoc, matrix);
    }

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(viewMatrixLoc, matrix);
    }

    void loadLightPosition(glm::vec3 pos = glm::vec3(1.0f)) {
        this->setVec3(lightPositionLoc, pos);
    }

    void loadLightColor(glm::vec3 color = glm::vec3(1.0f)) {
        this->setVec3(lightColorLoc, color);
    }

protected:
    void getAllUniformLocations() {
        transformationMatrixLoc = getUniformLocation(transformationMatrix);
        projectionMatrixLoc = getUniformLocation(projectionMatrix);
        viewMatrixLoc = getUniformLocation(viewMatrix);
        lightPositionLoc = getUniformLocation(lightPosition);
        lightColorLoc = getUniformLocation(lightColor);
    }

};
#endif //ENGINE_STATICSHADER_H
