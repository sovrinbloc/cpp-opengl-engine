//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_BOUNDINGBOXDATA_H
#define ENGINE_BOUNDINGBOXDATA_H

#include <utility>

#include "MeshData.h"

class BoundingBoxData : public MeshData {
private:
    bool mesh = false;
    static constexpr int kBboxIndices[] = {
            0, 1, 2, 3, 8, // Front wall
            4, 5, 6, 7, 8, // Back wall
            4, 0, 6, 2, 8, // Left wall
            1, 5, 3, 7, 8, // Right wall
            2, 3, 6, 7, 8, // Top wall
            0, 1, 4, 5
    };
public:
    explicit BoundingBoxData(std::vector<float> vertices,
                    std::vector<int> indices = std::vector<int>(BoundingBoxData::kBboxIndices, BoundingBoxData::kBboxIndices +
                                                                                      sizeof(BoundingBoxData::kBboxIndices) /
                                                                                      sizeof(int)),
                    bool mesh = false) :
            mesh(mesh), MeshData(std::move(vertices), std::move(indices)) {}

            BoundingBoxData(){}

    bool isMesh() const {
        return mesh;
    }
};

#endif //ENGINE_BOUNDINGBOXDATA_H
