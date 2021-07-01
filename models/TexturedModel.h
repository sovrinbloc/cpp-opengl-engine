//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_TEXTUREDMODEL_H
#define ENGINE_TEXTUREDMODEL_H

#include "RawModel.h"
#include "../textures/ModelTexture.h"
class TexturedModel {
private:
    RawModel *rawModel;
    ModelTexture *texture;

public:
    TexturedModel (RawModel *model, ModelTexture *texture) {
        this->rawModel = model;
        this->texture = texture;
    }

    RawModel *getRawModel() {
        return this->rawModel;
    }

    ModelTexture *getModelTexture() {
        return this->texture;
    }
};
#endif //ENGINE_TEXTUREDMODEL_H
