//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAINRENDERER_H
#define ENGINE_TERRAINRENDERER_H
#include "glm/glm.hpp"
#include "../toolbox/Maths.h"
#include "../shaders/TerrainShader.h"
#include "../terrain/Terrain.h"

class TerrainRenderer {
private:
    TerrainShader *shader;

public:
    TerrainRenderer(TerrainShader *shader, glm::mat4 projectionMatrix) {
        this->shader = shader;
        shader->start();
        shader->loadProjectionMatrix(projectionMatrix);
        shader->stop();
    }

    void render(std::vector<Terrain*> *terrains) {
        for (Terrain* terrain: *terrains) {
            prepareTerrain(terrain);
            loadModelMatrix(terrain);
            glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);

        }
        unbindTexturedModel();

    }

private:
    void prepareTerrain(Terrain *terrain) {
        RawModel *rawModel = terrain->getModel();

        // bind the current vao
        glBindVertexArray(rawModel->getVaoID());

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        ModelTexture *texture = terrain->getTexture();
        shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity(), texture->getAmbient());
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        texture->bindTexture();

    }

    void unbindTexturedModel() {
        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindVertexArray(0);
    }

    void loadModelMatrix(Terrain *terrain) {
        // creates the matrices to be passed into the shader
        glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain->getX(), 0.0f, terrain->getZ()));
        shader->loadTransformationMatrix(transformationMatrix);
    }
};
#endif //ENGINE_TERRAINRENDERER_H
