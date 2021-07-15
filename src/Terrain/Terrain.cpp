//
// Created by Joseph Alai on 7/6/21.
//

#include "Terrain.h"
#include "../Toolbox/Maths.h"

Terrain::Terrain(int gridX, int gridZ, Loader *loader, TerrainTexturePack *texturePack, TerrainTexture *blendMap,
                 const std::string &heightMap) : heightMap(Heightmap(heightMap)) {
    this->texturePack = texturePack;
    this->blendMap = blendMap;
    this->x = (float) gridX * SIZE;
    this->z = (float) gridZ * SIZE;
    this->model = generateTerrain(loader);
}

RawModel *Terrain::generateTerrain(Loader *loader) {
    int VERTEX_COUNT = heightMap.getImageInfo().height;
    heights = std::vector<std::vector<float>>(VERTEX_COUNT, std::vector<float>(VERTEX_COUNT));

    int count = VERTEX_COUNT * VERTEX_COUNT;

    std::vector<GLfloat> vertices(count * 3);
    vertices.reserve(count * 3);
    std::vector<GLfloat> normals(count * 3);
    normals.reserve(count * 3);
    std::vector<GLfloat> textureCoords(count * 2);
    textureCoords.reserve(count * 2);
    std::vector<GLint> indices(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));
    indices.reserve(6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1));

    int vertexPointer = 0;
    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {
            vertices[vertexPointer * 3] = (float) j / ((float) VERTEX_COUNT - 1) * SIZE;
            float height = heightMap.getHeight(j, i);
            heights[j][i] = height;
            vertices[vertexPointer * 3 + 1] = height;
            vertices[vertexPointer * 3 + 2] = (float) i / ((float) VERTEX_COUNT - 1) * SIZE;
            glm::vec3 normal = calculateNormal(j, i);
            normals[vertexPointer * 3] = normal.x;
            normals[vertexPointer * 3 + 1] = normal.y;
            normals[vertexPointer * 3 + 2] = normal.z;
            textureCoords[vertexPointer * 2] = (float) j / ((float) VERTEX_COUNT - 1);
            textureCoords[vertexPointer * 2 + 1] = (float) i / ((float) VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            indices[pointer++] = topLeft;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = topRight;
            indices[pointer++] = topRight;
            indices[pointer++] = bottomLeft;
            indices[pointer++] = bottomRight;
        }
    }
    return loader->loadToVAO(vertices, textureCoords, normals, indices);
}

glm::vec3 Terrain::calculateNormal(int x, int z) {
    float heightL = heightMap.getHeight(x - 1, z);
    float heightR = heightMap.getHeight(x + 1, z);
    float heightD = heightMap.getHeight(x, z - 1);
    float heightU = heightMap.getHeight(x, z + 1);
    glm::vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
    return glm::normalize(normal);
}

Heightmap Terrain::getHeightMap() {
    return heightMap;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ) {
    float terrainX = worldX - this->x;
    float terrainZ = worldZ - this->z;
    float gridSquareSize = SIZE / ((float) heights.size() - 1);
    int gridX = (int) floor(terrainX / gridSquareSize);
    int gridZ = (int) floor(terrainZ / gridSquareSize);

    if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0) {
        return 0;
    }

    float xCoord = (float) ((int) terrainX % (int) gridSquareSize) / gridSquareSize;
    float zCoord = (float) ((int) terrainZ % (int) gridSquareSize) / gridSquareSize;

    if (xCoord <= (1 - zCoord)) {
        return Maths::barryCentric(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1,
                                                                                     heights[gridX + 1][gridZ], 0),
                                   glm::vec3(0,
                                             heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
    } else {
        return Maths::barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(1,
                                                                                         heights[gridX + 1][gridZ +
                                                                                                            1], 1),
                                   glm::vec3(0,
                                             heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
    }
}