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
#include "BbData.h"


class OBJLoader {
public:
    static ModelData loadAssImp(std::string path);

    static ModelData loadObjModel(const std::string& filename);

    static BbData loadBoundingBox(const std::string& filename);

    static BbData loadBoundingBox(ModelData *data);

    static void processVertex(float vertex, float uv, float normal, std::vector<Vertex*> *vertices, std::vector<int> *indices);

    static int *convertIndicesListToArray(std::vector<int> indices);

    static float convertDataToArrays(std::vector<Vertex*> vertices, std::vector<glm::vec2> textures,
                                     std::vector<glm::vec3> normals, std::vector<float> *verticesArray, std::vector<float> *texturesArray,
                                     std::vector<float> *normalsArray);

    static void removeUnusedVertices(std::vector<Vertex*> *vertices);

    static void dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex,
                                               int newNormalIndex, std::vector<int>*indices, std::vector<Vertex*> *vertices);
};
#endif //ENGINE_OBJLOADER_H

