//
// Created by Joseph Alai on 7/27/21.
//

#ifndef ENGINE_FRAMEBUFFERS_H
#define ENGINE_FRAMEBUFFERS_H

#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB

#include <GLFW/glfw3.h>
#include "DisplayManager.h"

class FrameBuffers {

protected:
    static constexpr int kReflectionWidth = 320;

    static constexpr int refractionWidth = 1280;

private:
    static constexpr int kReflectionHeight = 180;

    static constexpr int kRefractionHeight = 720;

    GLuint reflectionFrameBuffer;

    GLuint reflectionTexture;

    GLuint reflectionDepthBuffer;

    GLuint refractionFrameBuffer;

    GLuint refractionTexture;

    GLuint refractionDepthTexture;

public:
    FrameBuffers();

    void cleanUp();

    void cleanUpReflection() const;

    void cleanUpRefraction() const;

    void bindReflectionFrameBuffer();

    void bindRefractionFrameBuffer();

    void unbindCurrentFrameBuffer() const;

    int getReflectionTexture() const;

    int getRefractionTexture() const;

    int getRefractionDepthTexture() const;

private:

    void initializeReflectionFrameBuffer();

    void initializeRefractionFrameBuffer();

    void bindFrameBuffer(GLuint frameBuffer, int width, int height);

    GLuint createFrameBuffer();

    GLuint createTextureAttachment(int width, int height);

    GLuint createDepthTextureAttachment(int width, int height);

    GLuint createDepthBufferAttachment(int width, int height);
};


#endif //ENGINE_FRAMEBUFFERS_H
