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
#include "../toolbox/FileSystem.h"
#include "ModelData.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <unordered_map>

using namespace std;

class OBJLoader {
public:

    static RawModel *loadAssImp(
            string path,
            Loader *loader
    ) {

        std::vector<unsigned short> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<glm::vec3> normals;

        Assimp::Importer importer;

        const aiScene *scene = importer.ReadFile(FileSystem::Path(path),
                                                 0/*aiProcess_JoinIdenticalVertices | aiProcess_SortByPType*/);
        if (!scene) {
            fprintf(stderr, importer.GetErrorString());
            getchar();
            return nullptr;
        }
        const aiMesh *mesh = scene->mMeshes[0]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

        // Fill vertices positions
        vertices.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D pos = mesh->mVertices[i];
            vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
        }

        // Fill vertices texture coordinates
        uvs.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
            uvs.push_back(glm::vec2(UVW.x, UVW.y));
        }

        // Fill vertices normals
        normals.reserve(mesh->mNumVertices);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            aiVector3D n = mesh->mNormals[i];
            normals.push_back(glm::vec3(n.x, n.y, n.z));
        }


        // Fill face indices
        indices.reserve(3 * mesh->mNumFaces);
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            // Assume the model has only triangles.
            indices.push_back(mesh->mFaces[i].mIndices[0]);
            indices.push_back(mesh->mFaces[i].mIndices[1]);
            indices.push_back(mesh->mFaces[i].mIndices[2]);
        }

        vector<GLfloat> outVertices, outUvs;
        vector<GLint> outIndices(indices.begin(), indices.end());
        for (int i = 0; i < vertices.size(); i++) {
            outVertices.push_back(vertices[i].x);
            outVertices.push_back(vertices[i].y);
            outVertices.push_back(vertices[i].z);
            outUvs.push_back(uvs[i].x);
            outUvs.push_back(uvs[i].y);
        }
        // The "scene" pointer will be deleted automatically by "importer"
        return loader->loadToVAO(outVertices, outUvs, outIndices);
    }


    static RawModel *loadObjModel(std::string filename, Loader *loader) {

        std::vector<Vertex> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textures;
        std::vector<GLint> indices;

        FILE *file = std::fopen(FileSystem::Path(std::move(filename)).c_str(), "r");
        if (file == nullptr) {
            printf("Impossible to open the file !\n");
            return nullptr;
        }

        while (true) {
            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // EOF = End Of File. Quit the loop.
            if (strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                Vertex *newVertex = new Vertex(vertices.size(), vertex);
                vertices.push_back(*newVertex);
            } else if (strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                textures.push_back(uv);
            } else if (strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                normals.push_back(normal);
            } else if (strcmp(lineHeader, "f") == 0) {

                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0],
                                     &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2],
                                     &uvIndex[2], &normalIndex[2]);

                if (matches != 9) {
                    printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                    return nullptr;
                }
                processVertex(vertexIndex[0], uvIndex[0], normalIndex[0], &vertices, &indices);
                processVertex(vertexIndex[1], uvIndex[1], normalIndex[1], &vertices, &indices);
                processVertex(vertexIndex[2], uvIndex[2], normalIndex[2], &vertices, &indices);
            }
        }

        removeUnusedVertices(&vertices);

        float verticesArray[vertices.size() * 3];
        float texturesArray[vertices.size() * 2];
        float normalsArray[vertices.size() * 3];

        float furthest = convertDataToArrays(&vertices, &textures, &normals, verticesArray,
                                             texturesArray, normalsArray);
        int *indicesArray = convertIndicesListToArray(indices);
        ModelData data(verticesArray, texturesArray, normalsArray, indicesArray, furthest);

        vector<float> outVertices, outNormals, outTextures;
        for (float vertex : verticesArray) {
            outVertices.push_back(vertex);
        }
        for (float tex : texturesArray) {
            outTextures.push_back(tex);
            printf("%f\n", tex);
        }


        std::fclose(file);
        return loader->loadToVAO(outVertices, outTextures, indices);
    }

    static void processVertex(float vertex, float uv, float normal, vector<Vertex> *vertices, vector<int> *indices) {
        int index = vertex - 1;
        auto currentVertex = (*vertices)[index];

        int textureIndex = uv - 1;
        int normalIndex = normal - 1;
        if (!currentVertex.isSet()) {
            currentVertex.setTextureIndex(textureIndex);
            currentVertex.setNormalIndex(normalIndex);
            indices->push_back(index);
        } else {
            dealWithAlreadyProcessedVertex(&currentVertex, textureIndex, normalIndex, indices,
                                           vertices);
        }
    }

     static int *convertIndicesListToArray(vector<int> indices) {
        int *indicesArray = new int[indices.size()];
        for (int i = 0; i < indices.size(); i++) {
            indicesArray[i] = indices[i];
        }
        return indicesArray;
    }

    static float convertDataToArrays(vector<Vertex> *vertices, vector<glm::vec2> *textures,
                                     vector<glm::vec3> *normals, float verticesArray[], float texturesArray[],
                                     float normalsArray[]) {
        float furthestPoint = 0;
        for (int i = 0; i < vertices->size(); i++) {
            auto currentVertex = (*vertices)[i];
            if (currentVertex.getLength() > furthestPoint) {
                furthestPoint = currentVertex.getLength();
            }
            glm::vec3 position = currentVertex.getPosition();
            glm::vec2 textureCoord = (*textures)[currentVertex.getTextureIndex()];
            glm::vec3 normalVector = (*normals)[currentVertex.getNormalIndex()];
            verticesArray[i * 3] = position.x;
            verticesArray[i * 3 + 1] = position.y;
            verticesArray[i * 3 + 2] = position.z;
            texturesArray[i * 2] = textureCoord.x;
            texturesArray[i * 2 + 1] = 1 - textureCoord.y;
            normalsArray[i * 3] = normalVector.x;
            normalsArray[i * 3 + 1] = normalVector.y;
            normalsArray[i * 3 + 2] = normalVector.z;
        }
        return furthestPoint;
    }

    static void removeUnusedVertices(vector<Vertex> *vertices){
        for(Vertex vertex:*vertices){
            if(!vertex.isSet()){
                vertex.setTextureIndex(0);
                vertex.setNormalIndex(0);
            }
        }
    }

    static void dealWithAlreadyProcessedVertex(Vertex *previousVertex, int newTextureIndex,
                                               int newNormalIndex, vector<int>*indices, vector<Vertex> *vertices) {
        if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex)) {
            indices->push_back(previousVertex->getIndex());
        } else {
            Vertex *anotherVertex = previousVertex->getDuplicateVertex();
            if (anotherVertex != nullptr) {
                dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex,
                                               indices, vertices);
            } else {
                Vertex *duplicateVertex = new Vertex(vertices->size(), previousVertex->getPosition());
                duplicateVertex->setTextureIndex(newTextureIndex);
                duplicateVertex->setNormalIndex(newNormalIndex);
                previousVertex->setDuplicateVertex(duplicateVertex);
                vertices->push_back(*duplicateVertex);
                indices->push_back(duplicateVertex->getIndex());
            }

        }
    }


//    void processVertex(string vertexData[], std::vector<int> indices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals,)

private:

};
#endif //ENGINE_OBJLOADER_H
