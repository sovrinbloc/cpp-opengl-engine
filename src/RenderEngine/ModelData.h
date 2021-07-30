//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_MODELDATA_H
#define ENGINE_MODELDATA_H

#include "glm/glm.hpp"
#include "MeshData.h"
#include <iostream>
#include <utility>
#include <vector>

struct BoxData {
    glm::vec3 vLowerLeftFront = glm::vec3(999999.0f, 999999.0f, -999999.0f);
    glm::vec3 vUpperRightBack = glm::vec3(-999999.0f, -999999.0f, 999999.0f);
    std::vector<int> indices =
            {
                    0, 1, 2, 3, 8, // Front wall
                    4, 5, 6, 7, 8, // Back wall
                    4, 0, 6, 2, 8, // Left wall
                    1, 5, 3, 7, 8, // Right wall
                    2, 3, 6, 7, 8, // Top wall
                    0, 1, 4, 5     // Bottom wall
            };
    std::vector<float> vertices;
};

class ModelData : public MeshData {

public:
    ModelData(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals,
              std::vector<int> indices) :
            MeshData(std::move(vertices), std::move(textureCoords), std::move(normals),
                     std::move(indices)) {
    }
};

#endif //ENGINE_MODELDATA_H
