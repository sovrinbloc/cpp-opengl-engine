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
public:
    GLuint attribute;
    StaticShader(const char *vertexPath = VertexPath, const char *fragmentPath = FragmentPath, const char *geometryPath = nullptr) : ShaderProgram(vertexPath, fragmentPath, geometryPath) {
        ShaderProgram(vertexPath, fragmentPath);
        bindAttribute(0, position);
        bindAttribute(1, texture);
    }
};
#endif //ENGINE_STATICSHADER_H
