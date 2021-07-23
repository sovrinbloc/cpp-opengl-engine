//
// Created by Joseph Alai on 7/22/21.
//

#ifndef ENGINE_FONTSHADER_H
#define ENGINE_FONTSHADER_H


#include "../Shaders/ShaderProgram.h"
#include "../RenderEngine/DisplayManager.h"
#include <glm/gtc/matrix_transform.hpp>

class FontShader : public ShaderProgram{
private:

    constexpr static const char *VertexPath = "/src/FontRendering/Shaders/VertexShader.glsl";
    constexpr static const char *FragmentPath = "/src/FontRendering/Shaders/FragmentShader.glsl";
    // attribute names
    const std::string vertex = "vertex";

    // uniform names
    const std::string projectionMatrix = "projection";
    const std::string textColor = "textColor";

    GLint location_projectionMatrix;
    GLint location_textColor;
public:
    FontShader();

    void bindAttributes() override;

    void loadProjectionMatrix(glm::mat4 matrix = glm::ortho(0.0f, static_cast<float>(DisplayManager::Width()), 0.0f, static_cast<float>(DisplayManager::Height())));

    void loadTextColor(glm::vec3 textColor = glm::vec3(0.0f));

protected:
    void getAllUniformLocations() override;
};


#endif //ENGINE_FONTSHADER_H
