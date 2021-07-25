//
// Created by Joseph Alai on 7/22/21.
//

#ifndef ENGINE_FONTRENDERER_H
#define ENGINE_FONTRENDERER_H


#include "FontShader.h"
#include "../RenderEngine/Loader.h"
#include "../FontMeshCreator/GUIText.h"

class FontRenderer {
private:
    FontShader *shader;
public:
    FontRenderer();
    void cleanUp();
    void render(std::vector<GUIText*> *texts);
    void render(std::map<FontType*, std::vector<GUIText*>> *texts);
    void renderText(GUIText* text);
    void endRendering();
    void prepare();
};


#endif //ENGINE_FONTRENDERER_H
