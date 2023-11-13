//
// Created by Joseph Alai on 8/2/21.
//

#ifndef ENGINE_OPENGLUTILS_H
#define ENGINE_OPENGLUTILS_H

#include "GLFW/glfw3.h"
#include "../Toolbox/Color.h"

class OpenGLUtils {
private:
    static bool cullingBackFace;
    static bool inWireframe;
    static bool isAlphaBlending;
    static bool additiveBlending;
    static bool antialiasing;
    static bool scissorTest;
    static bool depthTest;
    inline static int scissorBounds[4];

public:
    static void clearFrameBuffer(Color initColor);

    static void clearFrameBuffer();

    static void clearDepthBuffer();

    static void setStandardSettings(bool backfaceCulling, bool depthTesting, bool antialiasing);

    static void enableScissorTest(int x, int y, int width, int height);

    static void disableScissorTest();

    static void antialias(bool enable);

    static void enableAlphaBlending();

    static void enableAdditiveBlending();

    static void disableBlending();

    static void enableDepthTest(bool testing);

    static void enableDepthWriting(bool enable);

    static void enableDepthTesting();

    static void bindTextureToBank(int textureID, int bankID);

    static void bindTextureToBank(int textureID, int bankID, int lodBias);

    static void cullBackFaces(bool cull);

    static void goWireframe(bool goWireframe);
};


#endif //ENGINE_OPENGLUTILS_H
