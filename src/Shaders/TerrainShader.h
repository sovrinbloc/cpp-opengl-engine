//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAINSHADER_H
#define ENGINE_TERRAINSHADER_H
#include "../Entities/CameraInput.h"
#include "../Textures/ModelTexture.h"
#include "ShaderProgram.h"
#include "../Entities/Light.h"
#include "../Textures/TerrainTexturePack.h"


class TerrainShader : public ShaderProgram {
// attribute names
    const std::string position = "position";
    const std::string texture = "textureCoords";
    const std::string normal = "normal";

    // uniform names
    const std::string transformationMatrix = "transformationMatrix";
    const std::string projectionMatrix = "projectionMatrix";
    const std::string viewMatrix = "viewMatrix";
    const std::string lightColor = "lightColor";
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

    const std::string backgroundTexture = "backgroundTexture";
    const std::string rTexture = "rTexture";
    const std::string gTexture = "gTexture";
    const std::string bTexture = "bTexture";
    const std::string blendMap = "blendMap";

    GLint location_transformationMatrix;
    GLint location_projectionMatrix;
    GLint location_viewMatrix;
    GLint location_lightColor;
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
    
    GLint location_backgroundTexture;
    GLint location_rTexture;
    GLint location_gTexture;
    GLint location_bTexture;
    GLint location_blendMap;
public:
    GLuint attribute;

    TerrainShader();

    void bindAttributes();

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f));

    void loadLight(Light *light);

    void loadMaterial(Material material);

    void loadSkyColorVariable(glm::vec3 skyColor);

    void loadViewPosition(Camera *camera);

//    void connectTextureUnits(TerrainTexturePack *texturePack, TerrainTexture *blendMap);

    void connectTextureUnits();



protected:
    void getAllUniformLocations() override ;
};
#endif //ENGINE_TERRAINSHADER_H
