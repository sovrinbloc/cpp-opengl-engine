//
// Created by Joseph Alai on 7/7/21.
//

#ifndef ENGINE_ASSIMPMESHDATA_H
#define ENGINE_ASSIMPMESHDATA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Shaders/AssimpStaticShader.h"
#include <string>
#include <vector>
using namespace std;

struct VertexData {
    // vertex
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct TextureData {
    unsigned int id;
    string type;
    string path;
};



class AssimpMeshData {
public:
    // mesh Data
    vector<VertexData>       vertices;
    vector<unsigned int> indices;
    vector<TextureData>      textures;
    unsigned int VAO;

    // constructor
    AssimpMeshData(vector<VertexData> vertices, vector<unsigned int> indices, vector<TextureData> textures);

    // render the mesh
    void render(AssimpStaticShader *shader);

private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void setupMesh();
};

#endif //ENGINE_ASSIMPMESHDATA_H
