#include"OpenGLRenderContext.h"
#include <glad.h>


NAMESPACE_START

OpenGLRenderContext::OpenGLRenderContext(){
    this->setCurrentRenderContext(this);
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
    glBindVertexArray(vertexBufferLayoutID);

    // position attribute
    glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(location);
}

void OpenGLRenderContext::drawArrays(int first, int numVertex) {

    glDrawArrays(GL_TRIANGLES, first, numVertex);
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