//
// Created by Joseph Alai on 7/6/21.
//

#include "Loader.h"
#include "../Toolbox/FileSystem.h"

RawModel *Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLint> indices) {
    int vaoID = this->createVAO();
    this->bindIndicesBuffer(indices);
    this->storeDataInAttributeList(0, 3, positions);
    this->storeDataInAttributeList(1, 2, textureCoords);
    this->storeDataInAttributeList(2, 3, normals);
    this->unbindVAO();
    return new RawModel(vaoID, indices.size());
}

RawModel *Loader::loadToVAO(ModelData *data) {
    return loadToVAO(data->getVertices(), data->getTextureCoords(), data->getNormals(), data->getIndices());
}

RawModel *Loader::loadToVAO(std::vector<GLfloat> positions) {
    int vaoID = this->createVAO();
    this->storeDataInAttributeList(0, 2, positions);
    this->unbindVAO();
    return new RawModel(vaoID, positions.size() / 2);
}

TextureLoader *Loader::loadTexture(std::string fileName) {
    TextureLoader *tex = new TextureLoader(FileSystem::Texture(fileName), PNG);
    textures.push_back(tex->id);
    return tex;
}

void Loader::cleanUp() {
    for (unsigned int &vao : vaos) {
        glDeleteVertexArrays(1, &vao);
    }
    for (unsigned int &vbo : vbos) {
        glDeleteBuffers(1, &vbo);
    }
    for (unsigned int &tex : textures) {
        glDeleteTextures(1, &tex);
    }
}

GLuint Loader::createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    this->vaos.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::storeDataInAttributeList(GLuint attributeNumber, int coordinateSize, std::vector<GLfloat> positions) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    this->vbos.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, coordinateSize * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<GLint> indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices.front(), GL_STATIC_DRAW);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}