//
// Created by Joseph Alai on 7/28/21.
//

#ifndef ENGINE_BOUNDINGBOXDATA_H
#define ENGINE_BOUNDINGBOXDATA_H

#include <utility>

#include "MeshData.h"
#include "../Collision/AABB.h"

enum ClickBoxTypes {
    BOX = 0x00,
    SPHERE = 0x01,
    MESH = 0x02
};

class BoundingBoxData : public MeshData {
private:
    AABB boundingRegion;
    static constexpr int kBboxIndices[] = {
            0, 1, 2, 3, 8, // Front wall
            4, 5, 6, 7, 8, // Back wall
            4, 0, 6, 2, 8, // Left wall
            1, 5, 3, 7, 8, // Right wall
            2, 3, 6, 7, 8, // Top wall
            0, 1, 4, 5
    };
public:
    explicit BoundingBoxData(AABB boundingRegion, std::vector<float> vertices,
                    std::vector<int> indices = std::vector<int>(BoundingBoxData::kBboxIndices, BoundingBoxData::kBboxIndices +
                                                                                      sizeof(BoundingBoxData::kBboxIndices) /
                                                                                      sizeof(int))) :
            boundingRegion(boundingRegion), MeshData(std::move(vertices), std::move(indices)) {}

            BoundingBoxData(){}

    AABB getBoundingRegion() const {
        return boundingRegion;
    }
};

#endif //ENGINE_BOUNDINGBOXDATA_H
