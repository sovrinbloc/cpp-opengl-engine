//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "../entities/CameraInput.h"
#include "../entities/Entity.h"
#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
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

    Renderer(float screenWidth = 800.0f, float screenHeight = 600.0f) : ScreenWidth(screenWidth),
                                                                        ScreenHeight(screenHeight) {
        this->projectionMatrix = Maths::createProjectionMatrix(FOVY, screenWidth, screenHeight, NEAR_PLANE, FAR_PLANE);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
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
    void render(CameraInput *cameraInput, Entity *entity, StaticShader *shader) {
        TexturedModel *model = entity->getModel();
        RawModel *rawModel = model->getRawModel();
        Camera *viewCamera = cameraInput->getCamera();

        // bind the current vao
        glBindVertexArray(rawModel->getVaoID());

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        // creates the matrices to be passed into the shader
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(),
                                                                           entity->getScale());

        this->projectionMatrix = Maths::createProjectionMatrix(viewCamera->Zoom, ScreenWidth, ScreenHeight, NEAR_PLANE, FAR_PLANE);

        // checks for input on the keyboard.
        cameraInput->move();

        // bind texture
        model->getModelTexture()->bindTexture();

        // loads the matrices into the shader
        shader->loadTransformationMatrix(transformationMatrix);
        shader->loadProjectionMatrix(projectionMatrix);
        shader->loadViewMatrix(viewCamera->GetViewMatrix());
        shader->loadViewPosition(viewCamera);
        ModelTexture *texture = model->getModelTexture();
        shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity(), texture->getAmbient());

        // draw elements
        glDrawElements(GL_TRIANGLES, rawModel->getVertexCount(), GL_UNSIGNED_INT, 0);

        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    void updatePerspective(float width, float height) {
        this->ScreenWidth = width;
        this->ScreenHeight = height;
    }

};

#endif //ENGINE_RENDERER_H
