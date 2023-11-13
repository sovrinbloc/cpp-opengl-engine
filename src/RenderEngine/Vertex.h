//
// Created by Joseph Alai on 7/2/21.
//

#ifndef ENGINE_VERTEX_H
#define ENGINE_VERTEX_H
class Vertex {

private:
    int NO_INDEX = -1;

    glm::vec3 position{};
    int textureIndex = NO_INDEX;
    int normalIndex = NO_INDEX;
    Vertex *duplicateVertex = nullptr;
    int index;
    float length{};

public:
    Vertex(int index, glm::vec3 position) : index(index), position(position), length(sqrt(position.x * position.x + position.y * position.y + position.z * position.z)){}

    int getIndex() const {
        return index;
    }

    float getLength() const {
        return length;
    }

    bool isSet() const {
        return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
    }

    bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther) const {
        return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
    }

    void setTextureIndex(int textIndex) {
        this->textureIndex = textIndex;
    }

    void setNormalIndex(int normIndex) {
        this->normalIndex = normIndex;
    }

    glm::vec3 getPosition() const {
        return position;
    }

    int getTextureIndex() const {
        return textureIndex;
    }

    int getNormalIndex() const {
        return normalIndex;
    }

    Vertex *getDuplicateVertex() {
        return duplicateVertex;
    }

    void setDuplicateVertex(Vertex *dupeVertex) {
        this->duplicateVertex = dupeVertex;
    }

};
#endif //ENGINE_VERTEX_H
