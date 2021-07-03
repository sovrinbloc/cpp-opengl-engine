//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_STATICSHADER_H
#define ENGINE_STATICSHADER_H

#include "ShaderProgram.h"
#include "../entities/Light.h"

static const char *VertexPath = "/shaders/vertex_shader.glsl";
static const char *FragmentPath = "/shaders/fragment_shader.glsl";

class StaticShader : public ShaderProgram {
private:
    // attribute names
    const std::string position = "position";
    const std::string texture = "textureCoords";
    const std::string normal = "normal";

    // uniform names
    const std::string transformationMatrix = "transformationMatrix";
    const std::string projectionMatrix = "projectionMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string lightPosition = "lightPosition";
    const std::string lightColor = "lightColor";

    int location_transformationMatrix;
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_lightPosition;
    int location_lightColor;
public:
    GLuint attribute;

    StaticShader() : ShaderProgram(VertexPath, FragmentPath, nullptr) {
        this->initialize();
        this->loadTransformationMatrix();
    }

    void bindAttributes() {
        this->bindAttribute(0, position);
        this->bindAttribute(1, texture);
        this->bindAttribute(2, normal);
    }

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_transformationMatrix, matrix);
    }

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_projectionMatrix, matrix);
    }

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_viewMatrix, matrix);
    }

    void loadLight(Light *light) {
        this->setVec3(location_lightPosition, light->getPosition());
        this->setVec3(location_lightColor, light->getColor());
    }


protected:
    void getAllUniformLocations() {
        location_transformationMatrix = getUniformLocation(transformationMatrix);
        location_projectionMatrix = getUniformLocation(projectionMatrix);
        location_viewMatrix = getUniformLocation(viewMatrix);
        location_lightPosition = getUniformLocation(lightPosition);
        location_lightColor = getUniformLocation(lightColor);
    }

};

#endif //ENGINE_STATICSHADER_H
