//
// Created by Joseph Alai on 7/25/21.
//

#include "BoundingBoxRenderer.h"
#include "../Toolbox/Maths.h"
#include "RenderStyle.h"

BoundingBoxRenderer::BoundingBoxRenderer(BoundingBoxShader *shader, glm::mat4 projectionMatrix) :
        shader(shader) {

    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->stop();

}

void BoundingBoxRenderer::render(std::map<RawBoundingBox *, std::vector<Entity *>> *entities) {
    auto it = entities->begin();
    RawBoundingBox *pRawBox;
    while (it != entities->end()) {
        pRawBox = it->first;
        prepareRawBoundingBox(pRawBox);

        std::vector<Entity *> batch = entities->find(pRawBox)->second;
        batch = entities->find(pRawBox)->second;
        for (Entity *entity : batch) {
            prepareInstance(entity);

            // draw elements
            glDrawElements(GL_TRIANGLE_STRIP, pRawBox->getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindBox();
        it++;
    }
}

void BoundingBoxRenderer::prepareRawBoundingBox(RawBoundingBox *box) {
    glBindVertexArray(box->getVaoId());
    glEnableVertexAttribArray(0); // position

    glEnable(GL_PRIMITIVE_RESTART_INDEX);
    glPrimitiveRestartIndex(8);
}

void BoundingBoxRenderer::unbindBox() {
    glDisable(GL_PRIMITIVE_RESTART_INDEX);
    RenderStyle::enableCulling();

    // clean up
    glDisableVertexAttribArray(0); // position
    glBindVertexArray(0);
}

void BoundingBoxRenderer::prepareInstance(Entity *entity) {
    shader->loadBoxColor(entity->getBoundingBox()->getBoxColor());
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(),
                                                                       entity->getScale());
    shader->loadTransformationMatrix(transformationMatrix);
}
