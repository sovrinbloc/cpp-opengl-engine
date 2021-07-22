//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_TEXTUREDMODEL_H
#define ENGINE_TEXTUREDMODEL_H

#include "RawModel.h"
#include "../Textures/ModelTexture.h"


class TexturedModel {
private:
    RawModel *rawModel;
    ModelTexture *texture;
public:
    /**
     * @brief TexturedModel stores the RawModel [the VaoId] (from loaded mesh details),
     *        the ModelTexture [textureId], as well as other texture information such
     *        as transparency, number of columns for the textureAtlas
     *
     * @param model
     * @param texture
     */
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
