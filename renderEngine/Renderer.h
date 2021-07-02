//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
#include "../entities/Entity.h"
#include "../shaders/StaticShader.h"
#include "../toolbox/Maths.h"

static const float FOVY = 45.0f;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000;

class Renderer {
private:
    glm::mat4 projectionMatrix;
    float ScreenWidth = 800.0f;
    float ScreenHeight = 600.0f;
public:

    Renderer(float screenWidth, float screenHeight) : ScreenWidth(screenWidth), ScreenHeight(screenHeight) {
        this->projectionMatrix = Maths::createProjectionMatrix(FOVY, screenWidth, screenHeight, NEAR_PLANE, FAR_PLANE);
    }

    /**
     * @brief prepares and clears buffer and screen for each iteration of loop
     */
    void prepare() {
        // render
        // ------
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    }

    /**
     * @brief draws actual textures and shapes on the screen
     *
     * @param texturedModel
     */
    void render(Entity *entity, StaticShader *shader) {
        TexturedModel *model = entity->getModel();
        RawModel *rawModel = model->getRawModel();
        glBindVertexArray(rawModel->getVaoID());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(),
                                                                           entity->getScale());
        shader->loadTransformationMatrix(transformationMatrix);
        shader->loadProjectionMatrix(projectionMatrix);

        // bind texture
        model->getModelTexture()->bindTexture();

        // draw elements
        glDrawElements(GL_TRIANGLES, rawModel->getVertexCount(), GL_UNSIGNED_INT, 0);

        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }

    void updatePerspective(float width, float height) {
        this->ScreenWidth = width;
        this->ScreenHeight = height;
    }

};

#endif //ENGINE_RENDERER_H
