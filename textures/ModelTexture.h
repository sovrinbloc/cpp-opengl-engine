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
    float reflectivity = 0;
public:
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
        ModelTexture::reflectivity = reflectivity;
    }

};
#endif //ENGINE_MODELTEXTURE_H
