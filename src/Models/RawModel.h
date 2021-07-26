//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RAWMODEL_H
#define ENGINE_RAWMODEL_H
#include "RawData.h"
/**
 * @brief: RawModel is a reference class.
 *          It stores the vaoId and vertices count
 *          that was loaded into Loader (VAO)
 */
class RawModel : public RawData{
public:
    RawModel(unsigned int vaoId, unsigned long vertexCount) : RawData(vaoId, vertexCount) {}
};
#endif //ENGINE_RAWMODEL_H
