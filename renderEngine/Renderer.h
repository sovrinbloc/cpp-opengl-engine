//
// Created by Joseph Alai on 6/30/21.
//

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include "../models/RawModel.h"
#include "../models/TexturedModel.h"
class Renderer {
public:
    /**
     * @brief prepares and clears buffer and screen for each iteration of loop
     */
    void prepare() {
        // render
        // ------
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    /**
     * @brief draws actual textures and shapes on the screen
     *
     * @param texturedModel
     */
    void render(TexturedModel *texturedModel) {
        RawModel *model = texturedModel->getRawModel();
        glBindVertexArray(model->getVaoID());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        // bind texture
        texturedModel->getModelTexture()->bindTexture();

        // draw elements
        glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);

        // clean up
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
    }
};
#endif //ENGINE_RENDERER_H
