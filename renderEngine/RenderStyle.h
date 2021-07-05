//
// Created by Joseph Alai on 7/4/21.
//

#ifndef ENGINE_RENDERSTYLE_H
#define ENGINE_RENDERSTYLE_H
class RenderStyle {
public:
    static void enableCulling() {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    static void disableCulling() {
        glDisable(GL_CULL_FACE);
    }
};
#endif //ENGINE_RENDERSTYLE_H
