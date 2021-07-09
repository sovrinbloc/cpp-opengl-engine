//
// Created by Joseph Alai on 7/6/21.
//

#include "TerrainRenderer.h"
#include "../Toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader *shader, glm::mat4 projectionMatrix) {
    this->shader = shader;
    shader->start();
    shader->loadProjectionMatrix(projectionMatrix);
    shader->connectTextureUnits();
    shader->stop();
}

void TerrainRenderer::render(std::vector<Terrain *> *terrains) {
    for (Terrain *terrain: *terrains) {
        prepareTerrain(terrain);
        loadModelMatrix(terrain);
        glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);

    }
    unbindTexturedModel();

}

void TerrainRenderer::prepareTerrain(Terrain *terrain) {
    RawModel *rawModel = terrain->getModel();

    // bind the current vao
    glBindVertexArray(rawModel->getVaoID());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    bindTextures(terrain);
    shader->loadMaterial(terrain->getTexturePack()->getMaterial());
}

void TerrainRenderer::bindTextures(Terrain *terrain) {
    TerrainTexturePack *texturePack = terrain->getTexturePack();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturePack->getBackgroundTexture()->getTextureID());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texturePack->getRTexture()->getTextureID());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, texturePack->getGTexture()->getTextureID());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, texturePack->getBTexture()->getTextureID());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap()->getTextureID());
}

void TerrainRenderer::unbindTexturedModel() {
    // clean up
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain *terrain) {
    // creates the matrices to be passed into the shader
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(
            glm::vec3(terrain->getX(), 0.0f, terrain->getZ()));
    shader->loadTransformationMatrix(transformationMatrix);
}