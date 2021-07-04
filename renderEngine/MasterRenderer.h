//
// Created by Joseph Alai on 7/3/21.
//

#ifndef ENGINE_MASTERRENDERER_H
#define ENGINE_MASTERRENDERER_H
#include <map>
#include <iostream>
#include "../shaders/StaticShader.h"
#include "../entities/CameraInput.h"
#include "../entities/Camera.h"
#include "../toolbox/Maths.h"
#include "Renderer.h"

static const float FOVY = 45.0f;
static const float NEAR_PLANE = 0.1f;
static const float FAR_PLANE = 1000;

class MasterRenderer {
private:
    StaticShader *shader;
    Renderer *renderer;

    std::map<TexturedModel *, std::vector<Entity*>> *entities;
public:
    MasterRenderer() : shader(new StaticShader()), renderer( new Renderer(shader)) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        shader->loadProjectionMatrix(Maths::createProjectionMatrix(FOVY, ScreenWidth, ScreenHeight, NEAR_PLANE, FAR_PLANE));
        entities = new std::map<TexturedModel *, std::vector<Entity*>>;
    }

    void cleanUp() {
        shader->cleanUp();
    }

    void render(Light *sun, CameraInput *camera) {
        renderer->prepare();
        shader->start();
        shader->loadLight(sun);

        shader->loadViewPosition(CameraInput::getCamera());
        shader->loadViewMatrix(CameraInput::getCamera()->GetViewMatrix());

        // my additions
        shader->loadProjectionMatrix(Maths::createProjectionMatrix(camera->getCamera()->Zoom, ScreenWidth, ScreenHeight, NEAR_PLANE, FAR_PLANE));
        camera->move();

        renderer->render(entities);
        shader->stop();
        entities->clear();
    }

    void processEntity(Entity *entity) {
        TexturedModel *entityModel = entity->getModel();
        auto batchIterator = entities->find(entityModel);
        if (batchIterator != entities->end()) {
            batchIterator->second.push_back(entity);
        } else {
            std::vector<Entity *>newBatch;
            newBatch.push_back(entity);
            (*entities)[entityModel] = newBatch;
        }
        std::vector<Entity *> batch = entities->find(entityModel)->second;
    }

    void updatePerspective(float width, float height) {
        this->ScreenWidth = width;
        this->ScreenHeight = height;
    }


    // my additions
private:
    float ScreenWidth = 800.0f;
    float ScreenHeight = 600.0f;

};
#endif //ENGINE_MASTERRENDERER_H
