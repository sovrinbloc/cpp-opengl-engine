//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_STATICSHADER_H
#define ENGINE_STATICSHADER_H

#include "ShaderProgram.h"
class StaticShader : public ShaderProgram {
private:
     const char *VERTEX_FILE = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/vertex_shader.glsl";
     const char *FRAGMENT_FILE = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/fragment_shader.glsl";
     std::string variableName = "aPos";
public:
    GLuint attribute;
    StaticShader(const char *vertexPath = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/vertex_shader.glsl", const char *fragmentPath = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/fragment_shader.glsl", const char *geometryPath = nullptr) : ShaderProgram(vertexPath, fragmentPath, geometryPath) {
        ShaderProgram(vertexPath, fragmentPath);
        attribute = getAttribute(variableName);
    }
};
#endif //ENGINE_STATICSHADER_H
