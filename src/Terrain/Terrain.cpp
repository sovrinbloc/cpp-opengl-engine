//
// Created by Joseph Alai on 7/6/21.
//

#include "Terrain.h"

Terrain::Terrain(int gridX, int gridZ, Loader *loader, ModelTexture *texture) {
    this->texture = texture;
    this->x = (float)gridX * SIZE;
    this->z = (float)gridZ * SIZE;
    this->model = generateTerrain(loader);
}

RawModel *Terrain::generateTerrain(Loader *loader){
    int count = VERTEX_COUNT * VERTEX_COUNT;
    std::vector<GLfloat> vertices(count * 3); vertices.reserve(count * 3);
    std::vector<GLfloat> normals(count * 3); normals.reserve(count * 3);
    std::vector<GLfloat> textureCoords(count * 2); textureCoords.reserve(count*2);
    std::vector<GLint> indices(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)); indices.reserve(6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1));
    int vertexPointer = 0;
    for(int i=0;i<VERTEX_COUNT;i++){
        for(int j=0;j<VERTEX_COUNT;j++){
            vertices[vertexPointer*3] =  (float)j/((float)VERTEX_COUNT - 1) * SIZE;
            vertices[vertexPointer*3+1] = 0;
            vertices[vertexPointer*3+2] =  (float)i/((float)VERTEX_COUNT - 1) * SIZE;
            normals[vertexPointer*3] = 0;
            normals[vertexPointer*3+1] = 1;
            normals[vertexPointer*3+2] = 0;
            textureCoords[vertexPointer*2] = (float)j/((float)VERTEX_COUNT - 1);
            textureCoords[vertexPointer*2+1] = (float)i/((float)VERTEX_COUNT - 1);
            vertexPointer++;
        }
    }
    int pointer = 0;
    for(int gz=0;gz<VERTEX_COUNT-1;gz++){
        for(int gx=0;gx<VERTEX_COUNT-1;gx++){
            int topLeft = (gz*VERTEX_COUNT)+gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
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