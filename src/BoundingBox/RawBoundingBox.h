//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_RAWBOUNDINGBOX_H
#define ENGINE_RAWBOUNDINGBOX_H
#include "../Models/RawData.h"
class RawBoundingBox : public RawData{
private:
    bool mesh = false;
public:
    bool isMesh() const {
        return mesh;
    }

public:
    RawBoundingBox(unsigned int vaoId, unsigned long vertexCount, bool mesh = false) :
        mesh(mesh), RawData(vaoId, vertexCount) {}
};
#endif //ENGINE_RAWBOUNDINGBOX_H
