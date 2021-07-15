//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MODELTEXTURE_H
#define ENGINE_MODELTEXTURE_H

#include "TextureLoader.h"
#include "glm/glm.hpp"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

class ModelTexture : public TextureLoader {
public:
    ModelTexture(std::string filename, ImageType type,
                 Material
                 materials = Material{
                         .ambient =  glm::vec3(1.0f),
                         .diffuse =  glm::vec3(1.0f),
                         .specular =  glm::vec3(1.0f),
                         .shininess = 32.0f}
    ) ;

private:
    float shineDamper = 1;
    float reflectivity = 0.5;
    float ambient = 0.1;
    bool hasTransparency = false;
    bool useFakeLighting = false;
    Material material;

public:

    Material getMaterial() const {
        return material;
    }

    void setMaterial(Material material) {
        this->material = material;
    }

    bool isUseFakeLighting() const {
        return useFakeLighting;
    }

    void setUseFakeLighting(bool useFakeLighting) {
        this->useFakeLighting = useFakeLighting;
    }

    bool isHasTransparency() const {
        return hasTransparency;
    }

    void setHasTransparency(bool hasTransparency) {
        ModelTexture::hasTransparency = hasTransparency;
    }

    float getAmbient() {
        return ambient;
    }

    void setAmbient(float ambient) {
        this->ambient = ambient;
    }

    float getShineDamper() const {
        return shineDamper;
    }

    void setShineDamper(float shineDamper) {
        ModelTexture::shineDamper = shineDamper;
    }

    float getReflectivity() const {
        return reflectivity;
    }

    void setReflectivity(float reflectivity) {
        this->reflectivity = reflectivity;
    }

};

#endif //ENGINE_MODELTEXTURE_H
