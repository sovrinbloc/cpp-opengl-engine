//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_MESHDATA_H
#define ENGINE_MESHDATA_H

#include "glm/glm.hpp"
#include <utility>
#include <vector>
#include <iostream>
class MeshData {

protected:
    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<int> indices;
    glm::vec3 min;
    glm::vec3 max;

public:

    explicit MeshData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals,
    std::vector<int> indices, glm::vec3 min, glm::vec3 max) : vertices(std::move(vertices)), textureCoords(std::move(textureCoords)), normals(std::move(normals)),
    indices(std::move(indices)), min(min), max(max) {}
    MeshData(std::vector<float> vertices, std::vector<int> indices) : vertices(std::move(vertices)), indices(std::move(indices)){};

    MeshData(){}

    const glm::vec3 &getMin() const {
        return min;
    }

    void setMin(const glm::vec3 &min) {
        MeshData::min = min;
    }

    const glm::vec3 &getMax() const {
        return max;
    }

    void setMax(const glm::vec3 &max) {
        MeshData::max = max;
    }

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
