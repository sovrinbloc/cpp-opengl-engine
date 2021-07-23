//
// Created by Joseph Alai on 7/6/21.
//

#include "Loader.h"
#include "../Util/FileSystem.h"
#include "../Libraries/images/stb_image.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <utility>

/**
 * @name loadToVAO
 * @brief inputs positions, textureCoords, normals, and indices,
 *        creates a Vao, binds an indices buffer, stores the data
 *        in the Data Attribute Lists, unbinds, and creates and
 *        returns a RawModel (for terrains and entities mainly)
 * @param positions
 * @param textureCoords
 * @param normals
 * @param indices
 * @return
 */
RawModel *Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLint> indices) {
    unsigned int vaoId = createVAO();
    this->bindIndicesBuffer(indices);
    this->storeDataInAttributeList(0, 3, std::move(positions));
    this->storeDataInAttributeList(1, 2, std::move(textureCoords));
    this->storeDataInAttributeList(2, 3, std::move(normals));
    this->unbindVAO();
    return new RawModel(vaoId, indices.size());
}

/**
 * @name loadToVAO
 * @brief inputs a ModelData *data object, which includes all the vectors of vertex,
 *        normals, texCoords, and indices to store as VAO and return a RawModel. Used for
 *        meshes and terrains
 * @param data
 * @return
 */
RawModel *Loader::loadToVAO(ModelData *data) {
    return loadToVAO(data->getVertices(), data->getTextureCoords(), data->getNormals(), data->getIndices());
}

/**
 * @brief inputs positions and dimensions, creates VAO, return RawModel
 *        this is mainly for 2D models (gui, sky boxes).
 * @param positions
 * @param dimensions
 * @return
 */
RawModel *Loader::loadToVAO(std::vector<GLfloat> positions, int dimensions) {
    int vaoID = createVAO();
    this->storeDataInAttributeList(0, dimensions, positions);
    this->unbindVAO();
    return new RawModel(vaoID, positions.size() / dimensions);
}

FontModel *Loader::loadFontVAO(int vertices, int size, int bitSize) {
    GLuint vaoID = createVAO();
    GLuint vboID = createVBO();
    this->initDynamicAttributeList(vaoID, vboID, vertices, size, bitSize);
    this->unbindVAO();
    return new FontModel(vaoID, vboID, vertices);
}

GLuint Loader::createVBO() {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    vbos.push_back(vboID);
    return vboID;
}

/**
 * Loads a texture and returns it's id.
 * @param fileName
 * @return
 */
TextureLoader *Loader::loadTexture(std::string fileName) {
    TextureLoader *tex = new TextureLoader(FileSystem::Texture(std::move(fileName)), PNG);
    textures.push_back(tex->getId());
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
    GLuint vboID = createVBO();
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


void Loader::initDynamicAttributeList(GLuint attributeNumber, GLuint vboNumber, int vertices, int size, int bitSize) {
    glBindBuffer(GL_ARRAY_BUFFER, vboNumber);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, size * bitSize, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO() {
    glBindVertexArray(0);
}

unsigned int Loader::loadCubeMap(std::vector<std::string> faces) {

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    textures.push_back(textureID);
    return textureID;
}
