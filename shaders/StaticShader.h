//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_STATICSHADER_H
#define ENGINE_STATICSHADER_H

#include "ShaderProgram.h"
class StaticShader : public ShaderProgram {
private:
     std::string VERTEX_FILE = "src/shaders/vertex_shader.glsl";
     std::string FRAGMENT_FILE = "src/shaders/fragment_shader.glsl";
public:
    explicit StaticShader(const char *vertexPath = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/vertex_shader.glsl", const char *fragmentPath = "/Users/josephalai/Projects/games/cpp-mc/engine/shaders/fragment_shader.glsl", const char *geometryPath = nullptr) : ShaderProgram(vertexPath, fragmentPath, geometryPath) {
        ShaderProgram(vertexPath, fragmentPath);
    }

};
#endif //ENGINE_STATICSHADER_H
