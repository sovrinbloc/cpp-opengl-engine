//
// Created by Joseph Alai on 7/8/21.
//

#ifndef ENGINE_ASSIMPENTITY_H
#define ENGINE_ASSIMPENTITY_H

#include "../RenderEngine/AssimpEntityLoader.h"
#include "../Interfaces/Interactive.h"

class AssimpEntity : public Interactive {
private:
    AssimpMesh *model;
    BoundingBox *box;
    glm::vec3 position;
    glm::vec3 rotation;
    float scale;

public:

    explicit AssimpEntity(AssimpMesh *model, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
                 float scale = 1.0f);

    AssimpEntity(AssimpMesh *model, BoundingBox *box, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 rotation = glm::vec3(0),
                 float scale = 1.0f);

    AssimpMesh *getModel();

    BoundingBox *getBoundingBox() const override;

    void setBoundingBox(BoundingBox *box) override;

    glm::vec3 &getPosition () override;

    void setPosition(glm::vec3 translate) override;

    void increasePosition(glm::vec3 translate) override;

    glm::vec3 getRotation() override;

    void rotate(glm::vec3 rotate) override;

    void setRotation(glm::vec3 rotate) override;

    void increaseScale(float scaleSize) override;

    void setScale(float scaleSize) override;

    float getScale() const override;

    void setTransformation(glm::vec3 translate, glm::vec3 rotate, float scalar) override;

};

#endif //ENGINE_ASSIMPENTITY_H
