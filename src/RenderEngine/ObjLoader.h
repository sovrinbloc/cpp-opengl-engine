//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_OBJLOADER_H
#define ENGINE_OBJLOADER_H

#include <cstdio>
#include <string>
#include <utility>

#include "glm/glm.hpp"
#include "Loader.h"
#include "Vertex.h"
#include "ModelData.h"
#include "BoundingBoxData.h"
#include "AssimpEntityLoader.h"
#include "../Collision/BoundingRegion.h"

class OBJLoader {
public:
    static ModelData loadAssImp(std::string path);

    static ModelData loadObjModel(const std::string& filename);

    static BoundingBoxData loadBoundingBox(const std::string& filename, ClickBoxTypes boxType, BoundTypes boundType);

    static BoundingBoxData loadBoundingBox(ModelData &data, ClickBoxTypes boxType, BoundTypes boundType);

    static BoundingBoxData loadBoundingBox(AssimpMesh *data, ClickBoxTypes boxType, BoundTypes boundingType);

    static void processVertex(float vertex, float uv, float normal, std::vector<Vertex*> *vertices, std::vector<int> *indices);

    static int *convertIndicesListToArray(std::vector<int> indices);

    static float convertDataToArrays(std::vector<Vertex*> vertices, std::vector<glm::vec2> textures,
                                     std::vector<glm::vec3> normals, std::vector<float> *verticesArray, std::vector<float> *texturesArray,
                                     std::vector<float> *normalsArray);

    static void removeUnusedVertices(std::vector<Vertex*> *vertices);

    static void dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex,
                                               int newNormalIndex, std::vector<int>*indices, std::vector<Vertex*> *vertices);

    static vector<float> generateBox(glm::vec3 min, glm::vec3 max);

    static void generateSphere(ModelData &data, BoundingRegion &br);
};
#endif //ENGINE_OBJLOADER_H

