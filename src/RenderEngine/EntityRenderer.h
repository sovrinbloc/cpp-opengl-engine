//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_ENTITYRENDERER_H
#define ENGINE_ENTITYRENDERER_H
#include <map>

#include "../models/TexturedModel.h"
#include "../shaders/StaticShader.h"
#include "../entities/Entity.h"

class EntityRenderer {
private:
    StaticShader *shader;

public:

    EntityRenderer(StaticShader *shader);

    /**
     * @brief accepts a map[model]std::vector<Entity *>, and traverses through
     *        it, and draws them -- so as not to copy objects.
     * @param entities
     */
    void render(std::map<TexturedModel *, std::vector<Entity *>> *entities);

private:
    /**
     * @brief binds the attribute arrays of the model. disables
     *        or enables culling based on the transparency of the texture,
     *        loads the shine variables, and binds the texture.
     * @param model
     */
    void prepareTexturedModel(TexturedModel *model);

    /**
     * @brief unbinds the texture model after it's use.
     */
    void unbindTexturedModel();

    /**
     * @brief sets the initial transformation (view) matrix.
     * @param entity
     */
    void prepareInstance(Entity *entity);
};

#endif //ENGINE_ENTITYRENDERER_H
