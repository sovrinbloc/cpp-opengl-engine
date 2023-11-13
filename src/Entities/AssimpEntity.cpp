//
// Created by Joseph Alai on 7/30/21.
//
#include "AssimpEntity.h"



AssimpEntity::AssimpEntity(AssimpMesh *model, glm::vec3 position, glm::vec3 rotation, float scale) : model(model), position(position), rotation(rotation),
                                                                                                     scale(scale), box(
                nullptr) {}

AssimpEntity::AssimpEntity(AssimpMesh *model, BoundingBox *box, glm::vec3 position, glm::vec3 rotation, float scale) : model(model), box(box), position(position), rotation(rotation),
                                                                                                                       scale(scale) {}


AssimpMesh *AssimpEntity::getModel() {
    return this->model;
}

BoundingBox *AssimpEntity::getBoundingBox() const {
    return box;
}

void AssimpEntity::setBoundingBox(BoundingBox *box) {
    this->box = box;
}

glm::vec3 &AssimpEntity::getPosition() {
    return position;
}

void AssimpEntity::setPosition(glm::vec3 translate) {
    this->position = translate;
}

void AssimpEntity::increasePosition(glm::vec3 translate) {
    this->position += translate;
}
void AssimpEntity::setTransformation(glm::vec3 translate, glm::vec3 rotate, float scalar) {
    this->position = translate;
    this->rotation = rotate;
    this->scale = scalar;
}

glm::vec3 AssimpEntity::getRotation() {
    return this->rotation;
}

void AssimpEntity::rotate(glm::vec3 rotate) {
    this->rotation += rotate;
}

void AssimpEntity::setRotation(glm::vec3 rotate) {
    this->rotation = rotate;
}

void AssimpEntity::increaseScale(float scaleSize) {
    scale += scaleSize;
}

float AssimpEntity::getScale() const {
    return this->scale;
}

void AssimpEntity::setScale(float scaleSize) {
    this->scale = scaleSize;
}
