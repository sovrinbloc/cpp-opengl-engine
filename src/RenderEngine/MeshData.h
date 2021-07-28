//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_MESHDATA_H
#define ENGINE_MESHDATA_H

#include "glm/glm.hpp"
#include <vector>
#include <iostream>
class MeshData {

protected:
    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<int> indices;

public:
    MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals,
    std::vector<int> indices) : vertices(vertices), textureCoords(textureCoords), normals(normals),
    indices(indices) {}

    std::vector<float> getVertices() {
        return vertices;
    }

    std::vector<float> getTextureCoords() {
        return textureCoords;
    }

    std::vector<float> getNormals() {
        return normals;
    }

    std::vector<int> getIndices() {
        return indices;
    }
};


#endif //ENGINE_MESHDATA_H
