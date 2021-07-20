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
    static const int MAX_LIGHTS = 4;

    // attribute names
    const std::string position = "position";
    const std::string texture = "textureCoords";
    const std::string normal = "normal";

    // uniform names
    const std::string transformationMatrix = "transformationMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string projectionMatrix = "projectionMatrix";

    const std::string lightColor = "lightColor";
    const std::string skyColor = "skyColor";
    const std::string viewPosition = "viewPosition";

    const std::string lightAmbient = "light.ambient";
    const std::string lightDiffuse = "light.diffuse";
    const std::string lightSpecular = "light.specular";
    const std::string lightPosition = "light.position";

    const std::string materialShininess = "material.shininess";
    const std::string materialReflectivity = "material.reflectivity";


    GLint location_transformationMatrix;
    GLint location_projectionMatrix;
    GLint location_viewMatrix;
    GLint location_viewPosition;

    GLint location_skyColor;

    GLint location_lightAttenuation[MAX_LIGHTS];
    GLint location_lightAmbient[MAX_LIGHTS];
    GLint location_lightDiffuse[MAX_LIGHTS];
    GLint location_lightSpecular[MAX_LIGHTS];
    GLint location_lightPosition[MAX_LIGHTS];

    GLint location_materialShininess;
    GLint location_materialReflectivity;
public:
    GLuint attribute;

    ModelShader();

    void bindAttributes() ;

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadViewPosition(Camera *camera);

    void loadLight(std::vector<Light *>lights);

    void loadMaterial(Material material);

    void loadSkyColorVariable(glm::vec3 skyColor);



protected:
    void getAllUniformLocations() override;

};

#endif //ENGINE_MODELSHADER_H
