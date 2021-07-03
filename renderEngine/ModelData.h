//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_MODELDATA_H
#define ENGINE_MODELDATA_H

class ModelData {

private:
    float *vertices;
    float *textureCoords;
    float *normals;
    int *indices;
    float furthestPoint;

public:
    ModelData(float vertices[], float textureCoords[], float normals[], int indices[],
              float furthestPoint) {
        this->vertices = vertices;
        this->textureCoords = textureCoords;
        this->normals = normals;
        this->indices = indices;
        this->furthestPoint = furthestPoint;
    }

    float *getVertices() {
        return vertices;
    }

    float *getTextureCoords() {
        return textureCoords;
    }

    float *getNormals() {
        return normals;
    }

    int *getIndices() {
        return indices;
    }

    float getFurthestPoint() {
        return furthestPoint;
    }

};

#endif //ENGINE_MODELDATA_H
