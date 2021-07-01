//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RAWMODEL_H
#define ENGINE_RAWMODEL_H

class RawModel {
private:
    int vaoID;
    int vertexCount;
public:
    RawModel(int vaoID, int vertexCount) {
        this->vaoID = vaoID;
        this->vertexCount = vertexCount;
    }
    int getVaoID() {
        return this->vaoID;
    }
    int getVertexCount() {
        return this->vertexCount;
    }
};
#endif //ENGINE_RAWMODEL_H
