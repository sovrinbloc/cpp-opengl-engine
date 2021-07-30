//
// Created by Joseph Alai on 7/1/21.
//

#ifndef ENGINE_ENTITY_H
#define ENGINE_ENTITY_H

#include "glm/glm.hpp"
#include "../Models/TexturedModel.h"
#include "../BoundingBox/BoundingBox.h"
#include "../Interfaces/Interactive.h"

class Entity : public Interactive {
protected:
    TexturedModel *model;
    BoundingBox *box;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;
    int textureIndex = 0;

    Material material = {0.1, 0.9};
    bool activate = false;
public:

    /**
     * @brief Entity stores the TexturedModel (RawModel & Texture), and stores vectors
     *        to manipulate its' vertex, rotation, fontSize, (transformation).  It also
     *        stores the textureOffsets for textures in case there is a texture atlas.
     *
     * @param model
     * @param position
     * @param rotation
     * @param scale
     */
    explicit Entity(TexturedModel *model, BoundingBox *box, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
           float scale = 1.0f) : model(model), box(box), position(position), rotation(rotation), scale(scale) {}

    /**
      * @brief Entity stores the TexturedModel (RawModel & Texture), and stores vectors
      *        to manipulate its' vertex, rotation, fontSize, (transformation).  It also
      *        stores the textureOffsets and indices for textures in case there is a
      *        texture atlas.
      *
      * @param model
      * @param position
      * @param rotation
      * @param scale
      */
    explicit Entity(TexturedModel *model, BoundingBox *box, int textureIndex, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
           float scale = 1.0f) : model(model), box(box), textureIndex(textureIndex), position(position), rotation(rotation), scale(scale) {}

    BoundingBox *getBoundingBox() const override {
        return box;
    }

    void setBoundingBox(BoundingBox *box) override {
        this->box = box;
    }

    TexturedModel *getModel() {
        return this->model;
    }

    /**
     * @brief gets the yOffset for the texture
     * @return
     */
    float getTextureYOffset() {
        int column = textureIndex % model->getModelTexture()->getNumberOfRows();
        return static_cast<float>(column) / static_cast<float>(model->getModelTexture()->getNumberOfRows());
    }

    /**
     * @brief gets the xOffset for the texture
     * @return
     */
    float getTextureXOffset() {
        int row = textureIndex % model->getModelTexture()->getNumberOfRows();
        return static_cast<float>(row) / static_cast<float>(model->getModelTexture()->getNumberOfRows());
    }

    glm::vec3 &getPosition() override {
        return position;
    }


    void setPosition(glm::vec3 translate) {
        this->position = translate;
    }

    void increasePosition(glm::vec3 translate) {
        this->position += translate;
    }

    glm::vec3 getRotation() override {
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

    float getScale() const override {
        return this->scale;
    }

    void
    setTransformation(glm::vec3 translate = glm::vec3(1.0f), glm::vec3 rotate = glm::vec3(0.0f), float scalar = 1.0f) {
        this->position = translate;
        this->rotation = rotate;
        this->scale = scalar;
    }

    Material getMaterial() const {
        if (activate == false) {
            return this->model->getModelTexture()->getMaterial();
        }
        return material;
    }

    void setMaterial(Material material) {
        Entity::material = material;
    }

    bool hasMaterial() {
        return activate;
    }

    void activateMaterial() {
        activate = true;
    }

    void clearMaterial() {
        activate = false;
    }
};

#endif //ENGINE_ENTITY_H
