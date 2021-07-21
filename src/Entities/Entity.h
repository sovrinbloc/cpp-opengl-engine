//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include "glm/glm.hpp"
#include "../Models/TexturedModel.h"


class Entity {
protected:
    TexturedModel *model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
    int textureIndex = 0;

public:

    explicit Entity(TexturedModel *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
           float scale = 1.0f) : model(model), position(position), rotation(rotation), scale(scale) {}

    explicit Entity(TexturedModel *model, int textureIndex, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
           float scale = 1.0f) : model(model), textureIndex(textureIndex), position(position), rotation(rotation), scale(scale) {}

    TexturedModel *getModel() {
        return this->model;
    }

    float getTextureYOffset() {
        int column = textureIndex % model->getModelTexture()->getNumberOfRows();
        return (float)column / (float)model->getModelTexture()->getNumberOfRows();
    }

    float getTextureXOffset() {
        int row = textureIndex % model->getModelTexture()->getNumberOfRows();
        return (float)row / (float)model->getModelTexture()->getNumberOfRows();
    }


    glm::vec3 &getPosition() {
        return position;
    }

    void setPosition(glm::vec3 translate) {
        this->position = translate;
    }

    void increasePosition(glm::vec3 translate) {
        this->position += translate;
    }

    glm::vec3 getRotation() {
        return this->rotation;
    }

    void rotate(glm::vec3 rotate) {
        this->rotation += rotate;
    }

    void setRotation(glm::vec3 rotate) {
        this->rotation = rotate;
    }

    void increaseScale(float scaleSize) {
        scale += scaleSize;
    }

    void setScale(float scaleSize) {
        this->scale = scaleSize;
    }

    float getScale() const {
        return this->scale;
    }

    void
    setTransformation(glm::vec3 translate = glm::vec3(1.0f), glm::vec3 rotate = glm::vec3(0.0f), float scalar = 1.0f) {
        this->position = translate;
        this->rotation = rotate;
        this->scale = scalar;
    }
};

#endif //ENGINE_ENTITY_H
