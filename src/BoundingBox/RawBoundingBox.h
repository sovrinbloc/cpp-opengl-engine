//
// Created by Joseph Alai on 7/25/21.
//

#ifndef ENGINE_RAWBOUNDINGBOX_H
#define ENGINE_RAWBOUNDINGBOX_H
#include "../Models/RawData.h"
class RawBoundingBox : public RawData{
public:
    RawBoundingBox(unsigned int vaoId, unsigned long vertexCount) : RawData(vaoId, vertexCount) {}
};
#endif //ENGINE_RAWBOUNDINGBOX_H
