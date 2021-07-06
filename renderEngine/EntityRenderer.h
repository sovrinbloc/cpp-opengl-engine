//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_ENTITYRENDERER_H
#define ENGINE_ENTITYRENDERER_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <map>
#include <set>
#include <GLFW/glfw3.h>
#include "../entities/CameraInput.h"
#include "../entities/Entity.h"
#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
#include "../shaders/StaticShader.h"
#include "../toolbox/Maths.h"
#include "RenderStyle.h"

class EntityRenderer {
private:
    StaticShader *shader;

public:

    EntityRenderer(StaticShader *shader) {
        this->shader = shader;
    }

    /**
     * @brief accepts a map[model]std::vector<Entity *>, and traverses through
     *        it, and draws them -- so as not to copy objects.
     * @param entities
     */
    void render(std::map<TexturedModel *, std::vector<Entity *>> *entities) {
        std::map<TexturedModel *, std::vector<Entity *>>::iterator it = entities->begin();
        TexturedModel *model;
        while (it != entities->end()) {
            model = it->first;
            prepareTexturedModel(model);
            std::vector<Entity *> batch = entities->find(model)->second;
            batch = entities->find(model)->second;
            for (Entity *entity : batch) {
                prepareInstance(entity);
                // draw elements
                glDrawElements(GL_TRIANGLES, model->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
            }
            unbindTexturedModel();
            it++;
        }
    }

private:
    /**
     * @brief binds the attribute arrays of the model. disables
     *        or enables culling based on the transparency of the texture,
     *        loads the shine variables, and binds the texture.
     * @param model
     */
    void prepareTexturedModel(TexturedModel *model) {
        RawModel *rawModel = model->getRawModel();

        // bind the current vao
        glBindVertexArray(rawModel->getVaoID());

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        ModelTexture *texture = model->getModelTexture();

        if (texture->isHasTransparency()) {
            RenderStyle::disableCulling();
        }
        shader->loadFakeLightingVariable(texture->isUseFakeLighting());
        glActiveTexture(GL_TEXTURE0);
        // bind texture
        model->getModelTexture()->bindTexture();
    }

    /**
     * @brief unbinds the texture model after it's use.
     */
    void unbindTexturedModel() {
        RenderStyle::enableCulling();
        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    /**
     * @brief sets the initial transformation (view) matrix.
     * @param entity
     */
    void prepareInstance(Entity *entity) {
        // creates the matrices to be passed into the shader
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(),
                                                                           entity->getScale());
        shader->loadTransformationMatrix(transformationMatrix);
        shader->loadMaterial(entity->getModel()->getModelTexture()->getMaterial());
    }
};

#endif //ENGINE_ENTITYRENDERER_H
