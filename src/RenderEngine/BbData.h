//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_BBDATA_H
#define ENGINE_BBDATA_H

#include "MeshData.h"

class BbData : public MeshData {
private:
    bool mesh = false;
public:
    bool isMesh() const {
        return mesh;
    }

public:
    BbData(std::vector<float> vertices,
           std::vector<int> indices = {
                   0, 1, 2, 3, 8, // Front wall
                   4, 5, 6, 7, 8, // Back wall
                   4, 0, 6, 2, 8, // Left wall
                   1, 5, 3, 7, 8, // Right wall
                   2, 3, 6, 7, 8, // Top wall
                   0, 1, 4, 5     // Bottom wall
           }, bool mesh = false) : mesh(mesh), MeshData(vertices, textureCoords, normals, indices) {}
};

#endif //ENGINE_BBDATA_H
