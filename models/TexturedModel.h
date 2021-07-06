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
public:
    void setRawModel(RawModel *rawModel);

private:
    ModelTexture *texture;
public:
    TexturedModel(RawModel *model, ModelTexture *texture) {
        TexturedModel::rawModel = model;
        TexturedModel::texture = texture;
    }

    RawModel *getRawModel() {
        return TexturedModel::rawModel;
    }

    ModelTexture *getModelTexture() {
        return TexturedModel::texture;
    }
};

#endif //ENGINE_TEXTUREDMODEL_H
