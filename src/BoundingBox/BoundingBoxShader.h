//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_BOUNDINGBOXSHADER_H
#define ENGINE_BOUNDINGBOXSHADER_H

#include "../Shaders/ShaderProgram.h"
#include "../Entities/Camera.h"

class BoundingBoxShader : public ShaderProgram {
private:
    constexpr static const char *VertexPath = "/src/BoundingBox/BoundingBox/VertexShader.glsl";
    constexpr static const char *FragmentPath = "/src/BoundingBox/BoundingBox/FragmentShader.glsl";

    const std::string position = "position";

    const std::string boxColor = "color";
    const std::string transformationMatrix = "transformationMatrix";
    const std::string projectionMatrix = "projectionMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string viewPosition = "viewPosition";

    GLint location_transformationMatrix;
    GLint location_projectionMatrix;
    GLint location_viewMatrix;
    GLint location_viewPosition;
    GLint location_boxColor;

public:

    GLuint attribute;

    BoundingBoxShader();

    void bindAttributes() override;

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadBoxColor(glm::vec3 color = glm::vec3(0.0f));

    void loadViewPosition(Camera *camera);

protected:
    void getAllUniformLocations() override;

};


#endif //ENGINE_BOUNDINGBOXSHADER_H
