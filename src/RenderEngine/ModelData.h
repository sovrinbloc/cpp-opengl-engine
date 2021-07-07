//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_MODELDATA_H
#define ENGINE_MODELDATA_H

class ModelData {

private:
    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<int> indices;
    float furthestPoint;

public:
    ModelData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<int> indices,
              float furthestPoint) {
        this->vertices = vertices;
        this->textureCoords = textureCoords;
        this->normals = normals;
        this->indices = indices;
        this->furthestPoint = furthestPoint;
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

    float getFurthestPoint() {
        return furthestPoint;
    }

};

#endif //ENGINE_MODELDATA_H
