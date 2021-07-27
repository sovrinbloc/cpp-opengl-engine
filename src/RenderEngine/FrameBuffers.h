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
    FrameBuffers() {//call when loading the game
        initializeReflectionFrameBuffer();
        initializeRefractionFrameBuffer();
    }

    void cleanUp() {//call when closing the game
        cleanUpReflection();
        cleanUpRefraction();
    }

    void cleanUpReflection() const {
        glDeleteFramebuffers(1, &reflectionFrameBuffer);
        glDeleteTextures(1, &reflectionTexture);
        glDeleteRenderbuffers(1, &reflectionDepthBuffer);
    }

    void cleanUpRefraction() const {
        glDeleteFramebuffers(1, &refractionFrameBuffer);
        glDeleteTextures(1, &refractionTexture);
        glDeleteTextures(1, &refractionDepthTexture);
    }

    void bindReflectionFrameBuffer() {//call before rendering to this FBO
        bindFrameBuffer(reflectionFrameBuffer, kReflectionWidth, kReflectionHeight);
    }

    void bindRefractionFrameBuffer() {//call before rendering to this FBO
        bindFrameBuffer(refractionFrameBuffer, refractionWidth, kRefractionHeight);
    }

    void unbindCurrentFrameBuffer() const {//call to switch to default frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int width, height;
        glfwGetFramebufferSize(DisplayManager::window, &width, &height);
//        glfwGetFramebufferSize(DisplayManager::window, &width, &height);
//        glViewport(0, 0, DisplayManager::Width(), DisplayManager::Height());
        glViewport(0, 0, width, height);
    }

    int getReflectionTexture() const {//get the resulting texture
        return reflectionTexture;
    }

    int getRefractionTexture() const {//get the resulting texture
        return refractionTexture;
    }

    int getRefractionDepthTexture() const {//get the resulting depth texture
        return refractionDepthTexture;
    }

private:

    void initializeReflectionFrameBuffer() {
        reflectionFrameBuffer = createFrameBuffer();
        reflectionTexture = createTextureAttachment(kReflectionWidth, kReflectionHeight);
        reflectionDepthBuffer = createDepthBufferAttachment(kReflectionWidth, kReflectionHeight);
        unbindCurrentFrameBuffer();
    }

    void initializeRefractionFrameBuffer() {
        refractionFrameBuffer = createFrameBuffer();
        refractionTexture = createTextureAttachment(refractionWidth, kRefractionHeight);
        refractionDepthTexture = createDepthTextureAttachment(refractionWidth, kRefractionHeight);
        unbindCurrentFrameBuffer();
    }


    void bindFrameBuffer(GLuint frameBuffer, int width, int height) {
        glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glViewport(0, 0, width, height);
    }


    GLuint createFrameBuffer() {
        GLuint frameBuffer;
        glGenFramebuffers(1, &frameBuffer);
        //generate name for frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        //create the framebuffer
        glDrawBuffer(GL_COLOR_ATTACHMENT0);
        //indicate that we will always render to color attachment 0
        return frameBuffer;
    }


    GLuint createTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, (void *) 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                             texture, 0);
        return texture;
    }


    GLuint createDepthTextureAttachment(int width, int height) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
                     0, GL_DEPTH_COMPONENT, GL_FLOAT, (void *) 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                             texture, 0);
        return texture;
    }


    GLuint createDepthBufferAttachment(int width, int height) {
        GLuint depthBuffer;
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width,
                              height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER, depthBuffer);
        return depthBuffer;
    }
};


#endif //ENGINE_FRAMEBUFFERS_H
