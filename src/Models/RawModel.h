//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RAWMODEL_H
#define ENGINE_RAWMODEL_H

/**
 * @brief: RawModel is a reference class.
 *          It stores the vaoId and vertices count
 *          that was loaded into Loader (VAO)
 */
class RawModel {
private:
    unsigned int vaoId;
    long vertexCount;
public:
    RawModel(unsigned int vaoId, unsigned long vertexCount) {
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
#endif //ENGINE_RAWMODEL_H
