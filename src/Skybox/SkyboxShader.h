//
// Created by Joseph Alai on 7/20/21.
//

#ifndef ENGINE_SKYBOXSHADER_H
#define ENGINE_SKYBOXSHADER_H


#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"
#include "glm/glm.hpp"

class SkyboxShader : public ShaderProgram {
private:
    int location_projectionMatrix;
    int location_viewMatrix;
    int location_fogColor;

public:
    SkyboxShader();

    void loadProjectionMatrix(glm::mat4 matrix);

    void loadViewMatrix(glm::mat4 matrix);

    void loadFogColor(glm::vec3 color);

protected:
    void getAllUniformLocations();

    void bindAttributes();
};


#endif //ENGINE_SKYBOXSHADER_H
