//
// Created by Joseph Alai on 7/8/21.
//

#ifndef ENGINE_ASSIMPENTITYRENDERER_H
#define ENGINE_ASSIMPENTITYRENDERER_H
#include "../Entities/AssimpEntity.h"
#include "../Toolbox/Maths.h"
#include "AssimpEntityLoader.h"
#include <iostream>
#include <cstdio>
#include <map>

class AssimpEntityRenderer {
private:
    AssimpStaticShader *shader;

public:
    AssimpEntityRenderer(AssimpStaticShader *shader);

    /**
     * @brief accepts a map[model]std::vector<Entity *>, and traverses through
     *        it, and draws them -- so as not to copy objects.
     * @param scenes
     */
    void render(std::map<AssimpMesh *, std::vector<AssimpEntity *>> *scenes);


    /**
     * @brief sets the initial transformation (view) matrix.
     * @param scene
     */
    void prepareInstance(AssimpEntity *scene);

};
#endif //ENGINE_ASSIMPENTITYRENDERER_H
