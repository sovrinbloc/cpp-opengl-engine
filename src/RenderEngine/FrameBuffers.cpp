//
// Created by Joseph Alai on 7/27/21.
//

#include "FrameBuffers.h"

FrameBuffers::FrameBuffers() {//call when loading the game
    initializeReflectionFrameBuffer();
    initializeRefractionFrameBuffer();
}

void FrameBuffers::cleanUp() {//call when closing the game
    cleanUpReflection();
    cleanUpRefraction();
}

void FrameBuffers::cleanUpReflection() const {
    glDeleteFramebuffers(1, &reflectionFrameBuffer);
    glDeleteTextures(1, &reflectionTexture);
    glDeleteRenderbuffers(1, &reflectionDepthBuffer);
}

void FrameBuffers::cleanUpRefraction() const {
    glDeleteFramebuffers(1, &refractionFrameBuffer);
    glDeleteTextures(1, &refractionTexture);
    glDeleteTextures(1, &refractionDepthTexture);
}

void FrameBuffers::bindReflectionFrameBuffer() {//call before rendering to this FBO
    bindFrameBuffer(reflectionFrameBuffer, kReflectionWidth, kReflectionHeight);
}

void FrameBuffers::bindRefractionFrameBuffer() {//call before rendering to this FBO
    bindFrameBuffer(refractionFrameBuffer, refractionWidth, kRefractionHeight);
}

void FrameBuffers::unbindCurrentFrameBuffer() const {//call to switch to default frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, DisplayManager::FboWidth(), DisplayManager::FboHeight());
}

int FrameBuffers::getReflectionTexture() const {//get the resulting texture
    return reflectionTexture;
}

int FrameBuffers::getRefractionTexture() const {//get the resulting texture
    return refractionTexture;
}

int FrameBuffers::getRefractionDepthTexture() const {//get the resulting depth texture
    return refractionDepthTexture;
}

void FrameBuffers::initializeReflectionFrameBuffer() {
    reflectionFrameBuffer = createFrameBuffer();
    reflectionTexture = createTextureAttachment(kReflectionWidth, kReflectionHeight);
    reflectionDepthBuffer = createDepthBufferAttachment(kReflectionWidth, kReflectionHeight);
    unbindCurrentFrameBuffer();
}

void FrameBuffers::initializeRefractionFrameBuffer() {
    refractionFrameBuffer = createFrameBuffer();
    refractionTexture = createTextureAttachment(refractionWidth, kRefractionHeight);
    refractionDepthTexture = createDepthTextureAttachment(refractionWidth, kRefractionHeight);
    unbindCurrentFrameBuffer();
}

void FrameBuffers::bindFrameBuffer(GLuint frameBuffer, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, 0);//To make sure the texture isn't bound
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glViewport(0, 0, RETINA_SCALE(width), RETINA_SCALE(height));
}

GLuint FrameBuffers::createFrameBuffer() {
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    //generate name for frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    //create the framebuffer
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    //indicate that we will always render to color attachment 0
    return frameBuffer;
}

GLuint FrameBuffers::createTextureAttachment(int width, int height) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, RETINA_SCALE(width), RETINA_SCALE(height),
                 0, GL_RGB, GL_UNSIGNED_BYTE, (void *) 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                         texture, 0);
    return texture;
}

GLuint FrameBuffers::createDepthTextureAttachment(int width, int height) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, RETINA_SCALE(width), RETINA_SCALE(height),
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, (void *) 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                         texture, 0);
    return texture;
}

GLuint FrameBuffers::createDepthBufferAttachment(int width, int height) {
    GLuint depthBuffer;
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, RETINA_SCALE(width), RETINA_SCALE(height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthBuffer);
    return depthBuffer;
}