#include"OpenGLRenderContext.h"
#include <glad.h>
#include<Base/Texture2D.h>


NAMESPACE_START

OpenGLRenderContext::OpenGLRenderContext(){
    this->setCurrentRenderContext(this);
}

Texture2D* OpenGLRenderContext::createTexture2D(const TextureUsage& usage, const TextureFormat& textureFormat, const int width, const int height) {

    Texture2D* texture2D = new Texture2D(usage, textureFormat, width, height);
    
    return texture2D;
}

Texture2D * OpenGLRenderContext::loadTexture2D(const char* path) {

    Texture2D* texture2D = new Texture2D(path);

    return texture2D;
}

void OpenGLRenderContext::bindTexture(unsigned int bufferID, unsigned int bindingIndex) {
    glActiveTexture(GL_TEXTURE0 + bindingIndex);
    glBindTexture(GL_TEXTURE_2D, bufferID);
}

FrameBuffer OpenGLRenderContext::createFrameBuffer() {

    unsigned id = 0;
    glGenFramebuffers(1, &id);

    return FrameBuffer{ id, nullptr, nullptr};
}

void OpenGLRenderContext::beginRendering(const FrameBuffer& fbo) {

    glBindFramebuffer(GL_FRAMEBUFFER, fbo.id);
}

void OpenGLRenderContext::endRendering() {

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLRenderContext::bindIndexBuffer(unsigned int bufferID) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

unsigned int OpenGLRenderContext::createIndexBuffer(const void* data, int sizeInByte) {
    unsigned int bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInByte, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return bufferID;
}

unsigned int OpenGLRenderContext::createVertexBuffer(const void* data, int sizeInByte) {

    unsigned int bufferID;
    glGenBuffers(1, &bufferID);

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeInByte, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return bufferID;
}

unsigned int OpenGLRenderContext::createVertexBufferLayoutInfo(unsigned int vertexBufferID) {

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

    unsigned int vertextBufferAtributeID;
    glGenVertexArrays(1, &vertextBufferAtributeID);
    glBindVertexArray(vertextBufferAtributeID);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vertextBufferAtributeID;
}

void OpenGLRenderContext::setUpVertexBufferLayoutInfo(unsigned int vertexBufferID, unsigned int vertexBufferLayoutID, int size, int stride, int location, int offset) {

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    if (vertexBufferLayoutID > 0) {
        glBindVertexArray(vertexBufferLayoutID);
    }

    // position attribute
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
}

void OpenGLRenderContext::drawArrays(int first, int numVertex) {

    glDrawArrays(GL_TRIANGLES, first, numVertex);
}

void OpenGLRenderContext::drawElements(unsigned int count, const void* indices) {

    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, indices);
}

void OpenGLRenderContext::setDepthStencilState(const DepthStencilState& depthStencilState) {

    depthStencilState.depthTest ?glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    depthStencilState.depthWrite ? glDepthMask(true) : glDepthMask(false);

}

void OpenGLRenderContext::setClearAction(unsigned int action) {
    glClear(action);
}

void OpenGLRenderContext::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    
}

void OpenGLRenderContext::setShader(Shader* shader) {

}

void OpenGLRenderContext::bindVertexBuffer(unsigned int bufferID) {

    glBindVertexArray(bufferID);
}

OpenGLRenderContext::~OpenGLRenderContext() {
    this->setCurrentRenderContext(nullptr);
}

NAMESPACE_END