#include"OpenGLRenderContext.h"
#include <glad.h>


NAMESPACE_START

OpenGLRenderContext::OpenGLRenderContext() {

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

}

NAMESPACE_END