#include"OpenGLRenderContext.h"
#include <glad.h>


NAMESPACE_START

OpenGLRenderContext::OpenGLRenderContext() {

}

void OpenGLRenderContext::drawArrays(float* vextexBuffer) {

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

OpenGLRenderContext::~OpenGLRenderContext() {

}

NAMESPACE_END