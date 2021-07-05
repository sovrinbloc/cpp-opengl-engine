//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_MODELTEXTURE_H
#define ENGINE_MODELTEXTURE_H
#include "Texture.h"

class ModelTexture : public Texture{
public:
    ModelTexture(std::string filename, ImageType type) : Texture(filename, type) {}

private:
    float shineDamper = 1;
    float reflectivity = 0.5;
    float ambient = 0.1;
    bool hasTransparency = false;
    bool useFakeLighting = false;
public:
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
