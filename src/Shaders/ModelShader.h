//
// Created by Joseph Alai on 7/8/21.
//

#ifndef ENGINE_MODELSHADER_H
#define ENGINE_MODELSHADER_H


#include "../Entities/CameraInput.h"
#include "../Textures/ModelTexture.h"
#include "ShaderProgram.h"
#include "../Entities/Light.h"


class ModelShader : public ShaderProgram {
private:
    // attribute names
    const std::string position = "aPos";
    const std::string texture = "aTexCoords";
    const std::string normal = "aNormal";

    // uniform names
    const std::string transformationMatrix = "model";
    const std::string projectionMatrix = "projection";
    const std::string viewMatrix = "view";

    const std::string viewPosition = "viewPosition";


    GLint location_transformationMatrix;
    GLint location_projectionMatrix;
    GLint location_viewMatrix;
    GLint location_viewPosition;
public:
    GLuint attribute;

    ModelShader();

    void bindAttributes() ;

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadViewPosition(Camera *camera);



protected:
    void getAllUniformLocations() override;

};

#endif //ENGINE_MODELSHADER_H
