//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_LOADER_H
#define ENGINE_LOADER_H
#define GL_SILENCE_DEPRECATION

#include <vector>
#include "RawModel.h"
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

class Loader {
public:
    RawModel loadToVAO(float positions[]) {
        int vaoID = this->createVAO();
        this->storeDataInAttributeList(0, positions);
        this->unbindVAO();
        return RawModel(vaoID, 6);
    }
    
    void cleanUp() {
        for (unsigned int & vao : vaos) {
            glDeleteVertexArrays(1, &vao);
        }
        for (unsigned int & vbo : vbos) {
            glDeleteBuffers(1, &vbo);
        }
    }

private:
    std::vector<GLuint> vaos;
    std::vector<GLuint> vbos;

    GLuint createVAO() {
        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        this->vaos.push_back(vaoID);
        glBindVertexArray(vaoID);
        return vaoID;
    }

    void storeDataInAttributeList(int attributeNumber, float data[]){
        GLuint vboID;
        glGenBuffers(1, &vboID);
        this->vbos.push_back(vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat*) * 18, data, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void unbindVAO(){
        glBindVertexArray(0);
    }

};
#endif //ENGINE_LOADER_H
