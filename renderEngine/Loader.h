//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_LOADER_H
#define ENGINE_LOADER_H

#define GL_SILENCE_DEPRECATION
#include <vector>
#include "../models/RawModel.h"
#include "../textures/Texture.h"
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Loader {
public:
    RawModel *loadToVAO(std::vector<GLfloat> positions, std::vector<GLint> indices, GLuint attributeNumber) {
        int vaoID = this->createVAO();
        this->bindIndicesBuffer(indices);
        this->storeDataInAttributeList(attributeNumber, positions);
        this->unbindVAO();
        return new RawModel(vaoID, indices.size());
    }

    Texture *loadTexture(std::string fileName) {
        Texture *tex = new Texture(fileName, PNG);
        textures.push_back(tex->id);
        return tex;
    }

    void cleanUp() {
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

private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;
    std::vector<GLuint> textures;

    GLuint createVAO() {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        this->vaos.push_back(vaoID);
        glBindVertexArray(vaoID);
        return vaoID;
    }

    void storeDataInAttributeList(int attributeNumber, std::vector<GLfloat> positions) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        this->vbos.push_back(vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(positions[0]), &positions.front(), GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void bindIndicesBuffer(std::vector<GLint> indices) {
        GLuint vboID;
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices.front(), GL_STATIC_DRAW);
    }

    void unbindVAO() {
        glBindVertexArray(0);
    }

};

#endif //ENGINE_LOADER_H
