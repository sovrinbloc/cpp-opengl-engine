//
// Created by Joseph Alai on 7/7/21.
//

#ifndef ENGINE_ASSIMPENTITYLOADER_H
#define ENGINE_ASSIMPENTITYLOADER_H

#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Shaders/ModelShader.h"
#include "../Libraries/images/stb_image.h"

#include <iostream>

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>

#include "AssimpMeshData.h"

using namespace std;

/**
 * std::vector<AssimpEntity *> allScenes;
 * AssimpMesh assimpModel = AssimpMesh(FileSystem::Path("/src/Resources/Models/Backpack/backpack.obj"));
 * allScenes.push_back(new AssimpEntity(&assimpModel, glm::vec3(x, y, z), rot, Utils::randomFloat() * 2));
 * then in MainGameLoop renderer...
 * for (AssimpEntity *pack : allScenes) {
 *          renderer->processAssimpEntity(pack);
 *  }
 *  0r...
 *  renderer->processModel(&assimpModel); if it's a single model
 */
class AssimpMesh {

private:
    Material material;
public:

    // model data
    vector<TextureData> textures_loaded;    // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<AssimpMeshData> meshes;
    string directory;
    bool gammaCorrection;

    /**
     * @brief: constructor, expects a filepath to a 3D model.
     *
     * @example: AssimpMesh assimpModel = AssimpMesh(FileSystem::Path("/src/Resources/Models/Backpack/backpack.obj"));
     * @param path
     * @param gamma
     */
    AssimpMesh(string const &path,
               Material
          materials = Material{
                  .shininess = 1.0f,
                  .reflectivity = 0.5f
          }, bool gamma = false);

    // draws the model, and thus all its meshes
    void render(ModelShader *shader);

    const Material &getMaterial() const;

private:


    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    AssimpMeshData processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<TextureData> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);


    static unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);
};


#endif //ENGINE_ASSIMPENTITYLOADER_H
