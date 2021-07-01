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
    StaticShader(const char *vertexPath, const char *fragmentPath, const char *geometryPath) : ShaderProgram(vertexPath, fragmentPath, geometryPath) {
        ShaderProgram(VERTEX_FILE.c_str(), FRAGMENT_FILE.c_str());
    }

};
#endif //ENGINE_STATICSHADER_H
