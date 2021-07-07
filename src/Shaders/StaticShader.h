//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_STATICSHADER_H
#define ENGINE_STATICSHADER_H
#include "../Entities/CameraInput.h"
#include "../Textures/ModelTexture.h"
#include "ShaderProgram.h"
#include "../Entities/Light.h"


class StaticShader : public ShaderProgram {
private:
    // attribute names
    const std::string position = "position";
    const std::string texture = "textureCoords";
    const std::string normal = "normal";

    // uniform names
    const std::string transformationMatrix = "transformationMatrix";
    const std::string projectionMatrix = "projectionMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string lightColor = "lightColor";
    const std::string ambientStrength = "ambientStrength";
    const std::string useFakeLighting = "useFakeLighting";
    const std::string skyColor = "skyColor";
    const std::string viewPosition = "viewPosition";
    
    const std::string lightAmbient = "light.ambient";
    const std::string lightDiffuse = "light.diffuse";
    const std::string lightSpecular = "light.specular";
    const std::string lightPosition = "light.position";

    const std::string materialShininess = "material.shininess";
    const std::string materialAmbient = "material.ambient";
    const std::string materialDiffuse = "material.diffuse";
    const std::string materialSpecular = "material.specular";

    GLint location_transformationMatrix;
    GLint location_projectionMatrix;
    GLint location_viewMatrix;
    GLint location_lightColor;
    GLint location_useFakeLighting;
    GLint location_skyColor;
    GLint location_viewPosition;

    GLint location_lightAmbient;
    GLint location_lightDiffuse;
    GLint location_lightSpecular;
    GLint location_lightPosition;

    GLint location_materialShininess;
    GLint location_materialAmbient;
    GLint location_materialDiffuse;
    GLint location_materialSpecular;
public:
    GLuint attribute;

    StaticShader();

    void bindAttributes() ;

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) ;

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadLight(Light *light);
    
    void loadMaterial(Material material);

    void loadFakeLightingVariable(bool useFakeLighting);

    void loadSkyColorVariable(glm::vec3 skyColor);

    void loadViewPosition(Camera *camera);



protected:
    void getAllUniformLocations() override;

};

#endif //ENGINE_STATICSHADER_H
