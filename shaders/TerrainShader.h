//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAINSHADER_H
#define ENGINE_TERRAINSHADER_H
#include "../shaders/ShaderProgram.h"

static const char *TerrainVertexPath = "/shaders/terrain_vertex_shader.glsl";
static const char *TerrainFragmentPath = "/shaders/terrain_fragment_shader.glsl";

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
public:
    GLuint attribute;

    TerrainShader() : ShaderProgram(TerrainVertexPath, TerrainFragmentPath, nullptr) {
        this->initialize();
        this->loadTransformationMatrix();
    }

    void bindAttributes() {
        this->bindAttribute(0, position);
        this->bindAttribute(1, texture);
        this->bindAttribute(2, normal);
    }

    void loadTransformationMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_transformationMatrix, matrix);
    }

    void loadProjectionMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_projectionMatrix, matrix);
    }

    void loadViewMatrix(glm::mat4 matrix = glm::mat4(1.0f)) {
        this->setMat4(location_viewMatrix, matrix);
    }

    void loadLight(Light *light) {
        this->setVec3(location_lightPosition, light->getPosition());
        this->setVec3(location_lightColor, light->getColor());

        // for textures and lighting
        this->setVec3(location_lightAmbient, light->getLighting().ambient);
        this->setVec3(location_lightDiffuse, light->getLighting().diffuse);
        this->setVec3(location_lightSpecular, light->getLighting().specular);
        this->setVec3(location_lightPosition, light->getLighting().position);
    }

    void loadMaterial(Material *material) {
        this->setFloat(location_materialShininess, material->shininess);
        this->setVec3(location_materialAmbient, material->ambient);
        this->setVec3(location_materialDiffuse, material->diffuse);
        this->setVec3(location_materialSpecular, material->specular);
    }

    void loadSkyColorVariable(glm::vec3 skyColor) {
        this->setVec3(location_skyColor, skyColor);
    }

    void loadViewPosition(Camera *camera) {
        this->setVec3(location_viewPosition, camera->Position);
    }



protected:
    void getAllUniformLocations() override {
        location_transformationMatrix = getUniformLocation(transformationMatrix);
        location_projectionMatrix = getUniformLocation(projectionMatrix);
        location_viewMatrix = getUniformLocation(viewMatrix);
        location_lightPosition = getUniformLocation(lightPosition);
        location_lightColor = getUniformLocation(lightColor);
        location_skyColor = getUniformLocation(skyColor);

        location_viewPosition = getUniformLocation(viewPosition);

        // for textures and lighting
        location_lightAmbient = getUniformLocation(lightAmbient);
        location_lightDiffuse = getUniformLocation(lightDiffuse);
        location_lightSpecular = getUniformLocation(lightSpecular);
        location_lightPosition = getUniformLocation(lightPosition);

        location_materialShininess = getUniformLocation(materialShininess);
        location_materialAmbient = getUniformLocation(materialAmbient);
        location_materialDiffuse = getUniformLocation(materialDiffuse);
        location_materialSpecular = getUniformLocation(materialSpecular);
    }
};
#endif //ENGINE_TERRAINSHADER_H
