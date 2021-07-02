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
    std::string position = "position";
    std::string texture = "textureCoords";
    std::string transformationMatrix = "transformationMatrix";
public:
    GLuint attribute;
    StaticShader() : ShaderProgram(VertexPath, FragmentPath,nullptr) {
        initialize();
        loadTransformation();
    }

    void bindAttributes() {
        this->bindAttribute(0, position);
        this->bindAttribute(1, texture);
    }

    void loadTransformation(glm::mat4 matrix = glm::mat4(1.0f)) {
        setMat4(transformationMatrix.c_str(), matrix);
    }

protected:
    void getAllUniformLocations() {}

};
#endif //ENGINE_STATICSHADER_H
