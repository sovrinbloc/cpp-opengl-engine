//
// Created by Joseph Alai on 7/28/21.
//
#include "AssimpEntityRenderer.h"
AssimpEntityRenderer::AssimpEntityRenderer(AssimpStaticShader *shader) {
    this->shader = shader;
}

/**
 * @brief accepts a map[model]std::vector<Entity *>, and traverses through
 *        it, and draws them -- so as not to copy objects.
 * @param scenes
 */
void AssimpEntityRenderer::render(std::map<AssimpMesh *, std::vector<AssimpEntity *>> *scenes) {
    std::map<AssimpMesh *, std::vector<AssimpEntity *>>::iterator it = scenes->begin();
    AssimpMesh *model;
    while (it != scenes->end()) {
        model = it->first;
        std::vector<AssimpEntity *> batch = scenes->find(model)->second;
        batch = scenes->find(model)->second;
        for (AssimpEntity *scene : batch) {
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
void AssimpEntityRenderer::prepareInstance(AssimpEntity *scene) {
    // creates the matrices to be passed into the shader
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(scene->getPosition(), scene->getRotation(),
                                                                       scene->getScale());
    shader->loadTransformationMatrix(transformationMatrix);
    shader->loadMaterial(scene->getModel()->getMaterial());
}