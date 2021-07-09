//
// Created by Joseph Alai on 7/8/21.
//

#ifndef ENGINE_SCENERENDERER_H
#define ENGINE_SCENERENDERER_H
#include "../Entities/Scene.h"
#include "../Toolbox/Maths.h"
#include "SceneLoader.h"
#include <iostream>
#include <cstdio>
#include <map>

class SceneRenderer {
private:
    ModelShader *shader;

public:
    SceneRenderer(ModelShader *shader) {
        this->shader = shader;
    }

    /**
     * @brief accepts a map[model]std::vector<Entity *>, and traverses through
     *        it, and draws them -- so as not to copy objects.
     * @param scenes
     */
    void render(std::map<Model *, std::vector<Scene *>> *scenes) {
        std::map<Model *, std::vector<Scene *>>::iterator it = scenes->begin();
        Model *model;
        while (it != scenes->end()) {
            model = it->first;
            std::vector<Scene *> batch = scenes->find(model)->second;
            batch = scenes->find(model)->second;
            for (Scene *scene : batch) {
                prepareInstance(scene);
                // draw elements
                model->render(shader);
            }
            it++;
        }
    }


    /**
     * @brief sets the initial transformation (view) matrix.
     * @param scene
     */
    void prepareInstance(Scene *scene) {
        // creates the matrices to be passed into the shader
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(scene->getPosition(), scene->getRotation(),
                                                                           scene->getScale());
        shader->loadTransformationMatrix(transformationMatrix);
    }

};
#endif //ENGINE_SCENERENDERER_H
