//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MODELTEXTURE_H
#define ENGINE_MODELTEXTURE_H

#include "TextureLoader.h"
#include "glm/glm.hpp"

struct Material {
    float shininess;
    float reflectivity;
};

class ModelTexture : public TextureLoader {
public:
    ModelTexture(std::string filename, ImageType type,
                 Material materials = Material{
                         .shininess = 1.0f,
                         .reflectivity = 0.5f
                 });

private:
    bool hasTransparency = false;
    bool useFakeLighting = false;
    int numberOfRows = 1;
    Material material;
public:
    int getNumberOfRows() const;

    void setNumberOfRows(int numberOfRows);


    Material &getMaterial() {
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

};

#endif //ENGINE_MODELTEXTURE_H
