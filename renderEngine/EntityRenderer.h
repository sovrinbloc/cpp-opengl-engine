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

class EntityRenderer {
private:
    StaticShader *shader;

public:

    EntityRenderer(StaticShader *shader) {
        this->shader = shader;
    }


    // this is not fixxed. this needs to be finished
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
    void prepareTexturedModel(TexturedModel *model) {
        RawModel *rawModel = model->getRawModel();

        // bind the current vao
        glBindVertexArray(rawModel->getVaoID());

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        ModelTexture *texture = model->getModelTexture();
        shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity(), texture->getAmbient());
        glActiveTexture(GL_TEXTURE0);
        // bind texture
        model->getModelTexture()->bindTexture();

    }

    void unbindTexturedModel() {
        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    void prepareInstance(Entity *entity) {
        // creates the matrices to be passed into the shader
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(),
                                                                           entity->getScale());
        shader->loadTransformationMatrix(transformationMatrix);
    }
};

#endif //ENGINE_ENTITYRENDERER_H
