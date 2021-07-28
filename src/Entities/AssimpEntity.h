//
// Created by Joseph Alai on 7/8/21.
//

#ifndef ENGINE_ASSIMPENTITY_H
#define ENGINE_ASSIMPENTITY_H

#include "../RenderEngine/AssimpEntityLoader.h"

class AssimpEntity {
private:
    AssimpMesh *model;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;

public:

    AssimpEntity(AssimpMesh *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
                 float scale = 1.0f) : model(model), position(position), rotation(rotation),
                                scale(scale) {}

    AssimpMesh *getModel() {
        return this->model;
    }

    void setModel(AssimpMesh *texturedModel) {
        this->model = texturedModel;
    }


    glm::vec3 getPosition () {
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

    float getScale() {
        return this->scale;
    }

    void setTransformation(glm::vec3 translate = glm::vec3(1.0f), glm::vec3 rotate = glm::vec3(0.0f), float scalar = 1.0f) {
        this->position = translate;
        this->rotation = rotate;
        this->scale = scalar;
    }
};

#endif //ENGINE_ASSIMPENTITY_H
