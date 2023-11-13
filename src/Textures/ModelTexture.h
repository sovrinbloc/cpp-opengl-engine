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

/**
 * ModelTexture is a child of TextureLoader, which ultimately
 * just loads a texture, but also specifies other details, such as
 * how many textures in an atlas (if so chosen), using fake lighting,
 * transparency, and materials.
 */
class ModelTexture : public TextureLoader {
public:
    /**
     * @brief ModelTexture is a child of TextureLoader, which then ultimately
     *        adds more features for loading and returning the textureIds of
     *        images. But in this case, it also allows for texture atlases,
     *        materials, decisions of fake lighting, and transparency.
     * @param filename
     * @param type
     * @param materials
     */
    ModelTexture(std::string filename, ImageType type,
                 Material materials = Material{
                         .shininess = 1.0f,
                         .reflectivity = 0.5f
                 });
    ModelTexture(std::string filename, ImageType type,
                 bool useTransparency, bool useFakeLighting,
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
