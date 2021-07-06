//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_TERRAIN_H
#define ENGINE_TERRAIN_H
#include "../models/RawModel.h"
#include "../textures/ModelTexture.h"
#include "../renderEngine/Loader.h"
class Terrain {
private:
    const float SIZE = 800;
    const int VERTEX_COUNT = 128;

    float x;
    float z;
    RawModel *model;
    ModelTexture *texture;

public:
    float getX() const {
        return x;
    }

    void setX(float x) {
        this->x = x;
    }

    float getZ() const {
        return z;
    }

    void setZ(float z) {
        this->z = z;
    }

    RawModel *getModel() const {
        return model;
    }

    void setModel(RawModel *model) {
        this->model = model;
    }

    ModelTexture *getTexture() const {
        return texture;
    }

    void setTexture(ModelTexture *texture) {
        this->texture = texture;
    }

    Terrain(int gridX, int gridZ, Loader *loader, ModelTexture *texture) {
        this->texture = texture;
        this->x = (float)gridX * SIZE;
        this->z = (float)gridZ * SIZE;
        this->model = generateTerrain(loader);
    }

private:
    RawModel *generateTerrain(Loader *loader){
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
};
#endif //ENGINE_TERRAIN_H
