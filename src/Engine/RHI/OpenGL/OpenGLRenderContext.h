#pragma once

#include "RenderContext.h"

NAMESPACE_START

class Shader;
class Camera;

class OpenGLRenderContext : public RenderContext
{
public:

    OpenGLRenderContext();

    virtual void drawArrays(int first, int numVertex) override;

    virtual void setClearColor(float r, float g, float b, float a) override;

    virtual void setDepthStencilState(const DepthStencilState& depthStencilState) override;

    virtual void setClearAction(unsigned int action) override;

    virtual void setClearColor(float r, float g, float b, float a) override;

    virtual void setShader(Shader* shader) override;

    virtual void bindVertexBuffer(unsigned int bufferID) override;

    virtual ~OpenGLRenderContext();

    

};


NAMESPACE_END

