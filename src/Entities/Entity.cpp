//
// Created by Joseph Alai on 7/30/21.
//
#include "Entity.h"

Entity::Entity(TexturedModel *model, BoundingBox *box, glm::vec3 position, glm::vec3 rotation, float scale) : model(
        model), box(box), position(position), rotation(rotation), scale(scale) {}

Entity::Entity(TexturedModel *model, BoundingBox *box, int textureIndex, glm::vec3 position, glm::vec3 rotation,
               float scale) : model(model), box(box), textureIndex(textureIndex), position(position),
                              rotation(rotation), scale(scale) {}

BoundingBox *Entity::getBoundingBox() const {
    return box;
}

void Entity::setBoundingBox(BoundingBox *box) {
    this->box = box;
}

TexturedModel *Entity::getModel() {
    return this->model;
}

float Entity::getTextureXOffset() {
    int row = textureIndex % model->getModelTexture()->getNumberOfRows();
    return static_cast<float>(row) / static_cast<float>(model->getModelTexture()->getNumberOfRows());
}

float Entity::getTextureYOffset() {
    int column = textureIndex % model->getModelTexture()->getNumberOfRows();
    return static_cast<float>(column) / static_cast<float>(model->getModelTexture()->getNumberOfRows());
}

glm::vec3 &Entity::getPosition() {
    return position;
}

void Entity::setPosition(glm::vec3 translate) {
    this->position = translate;
}

void Entity::increasePosition(glm::vec3 translate) {
    this->position += translate;
}

glm::vec3 Entity::getRotation() {
    return this->rotation;
}

void Entity::rotate(glm::vec3 rotate) {
    this->rotation += rotate;
}

void Entity::setRotation(glm::vec3 rotate) {
    this->rotation = rotate;
}

void Entity::increaseScale(float scaleSize) {
    scale += scaleSize;
}

void Entity::setScale(float scaleSize) {
    this->scale = scaleSize;
}

float Entity::getScale() const {
    return this->scale;
}

void Entity::setTransformation(glm::vec3 translate, glm::vec3 rotate, float scalar) {
    this->position = translate;
    this->rotation = rotate;
    this->scale = scalar;
}

Material Entity::getMaterial() const {
    if (textureActivated == false) {
        return this->model->getModelTexture()->getMaterial();
    }
    return material;
}

void Entity::setMaterial(Material material) {
    Entity::material = material;
}

bool Entity::hasMaterial() const {
    return textureActivated;
}

void Entity::activateMaterial() {
    textureActivated = true;
}

void Entity::disableMaterial() {
    textureActivated = false;
}