//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_RAWDATA_H
#define ENGINE_RAWDATA_H
class RawData {
protected:
    unsigned int vaoId;
    long vertexCount;
public:
    RawData(unsigned int vaoId, unsigned long vertexCount) {
        this->vaoId = vaoId;
        this->vertexCount = vertexCount;
    }
    unsigned int getVaoId() {
        return vaoId;
    }
    int getVertexCount() {
        return vertexCount;
    }
};
#endif //ENGINE_RAWDATA_H
