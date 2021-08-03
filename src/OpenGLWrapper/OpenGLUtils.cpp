//
// Created by Joseph Alai on 8/2/21.
//

#include "OpenGLUtils.h"

bool OpenGLUtils::cullingBackFace = false;
bool OpenGLUtils::inWireframe = false;
bool OpenGLUtils::isAlphaBlending = false;
bool OpenGLUtils::additiveBlending = false;
bool OpenGLUtils::antialiasing = false;
bool OpenGLUtils::scissorTest = false;
bool OpenGLUtils::depthTest = false;

void OpenGLUtils::clearFrameBuffer(Color initColor) {
    glClearColor(initColor.getR(), initColor.getG(), initColor.getB(), initColor.getA());
    clearFrameBuffer();
}

void OpenGLUtils::clearFrameBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLUtils::clearDepthBuffer() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGLUtils::setStandardSettings(bool backfaceCulling, bool depthTesting, bool antialiasing) {
    cullBackFaces(backfaceCulling);
    enableDepthTest(depthTesting);
    antialias(antialiasing);
}

void OpenGLUtils::enableScissorTest(int x, int y, int width, int height) {
    if (!scissorTest) {
        scissorTest = true;
        glEnable(GL_SCISSOR_TEST);
    }
    if (x != scissorBounds[0] || y != scissorBounds[1] || width != scissorBounds[2] || height != scissorBounds[3]) {
        glScissor(x, y, width, height);
        scissorBounds[0] = x;
        scissorBounds[1] = y;
        scissorBounds[2] = width;
        scissorBounds[3] = height;
    }
}

void OpenGLUtils::disableScissorTest() {
    if (scissorTest) {
        scissorTest = false;
        glDisable(GL_SCISSOR_TEST);
    }
}

void OpenGLUtils::antialias(bool enable) {
    if (enable && !antialiasing) {
        glEnable(GL_MULTISAMPLE);
        antialiasing = true;
    } else if (!enable && antialiasing) {
        glDisable(GL_MULTISAMPLE);
        antialiasing = false;
    }
}

void OpenGLUtils::enableAlphaBlending() {
    if (!isAlphaBlending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        isAlphaBlending = true;
        additiveBlending = false;
    }
}

void OpenGLUtils::enableAdditiveBlending() {
    if (!additiveBlending) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        additiveBlending = true;
        isAlphaBlending = false;
    }
}

void OpenGLUtils::disableBlending() {
    if (isAlphaBlending || additiveBlending) {
        glDisable(GL_BLEND);
        isAlphaBlending = false;
        additiveBlending = false;
    }
}

void OpenGLUtils::enableDepthTest(bool testing) {
    if (testing && !depthTest) {
        glEnable(GL_DEPTH_TEST);
    } else if (!testing && depthTest) {
        glDisable(GL_DEPTH_TEST);
    }
    depthTest = testing;
}

void OpenGLUtils::enableDepthWriting(bool enable) {
    glDepthMask(enable);
}

void OpenGLUtils::bindTextureToBank(int textureID, int bankID) {
    glActiveTexture(GL_TEXTURE0 + bankID);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void OpenGLUtils::bindTextureToBank(int textureID, int bankID, int lodBias) {
    glActiveTexture(GL_TEXTURE0 + bankID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, lodBias);
    glActiveTexture(0);
}

void OpenGLUtils::cullBackFaces(bool cull) {
    if (cull && !cullingBackFace) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        cullingBackFace = true;
    } else if (!cull && cullingBackFace) {
        glDisable(GL_CULL_FACE);
        cullingBackFace = false;
    }
}

void OpenGLUtils::goWireframe(bool goWireframe) {
    if (goWireframe && !inWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        inWireframe = true;
    } else if (!goWireframe && inWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        inWireframe = false;
    }
}

void OpenGLUtils::enableDepthTesting() {
    if (goWireframe && !inWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        inWireframe = true;
    } else if (!goWireframe && inWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        inWireframe = false;
    }
}
