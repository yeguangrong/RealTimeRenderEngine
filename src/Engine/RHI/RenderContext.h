#pragma once

#include<Base/Constants.h>

NAMESPACE_START

class Shader;

struct DepthStencilState {
    bool depthTest = false;
    bool depthWrite = false;
};

class RenderContext
{
public:

    RenderContext() {};

    virtual void setClearColor(float r, float g, float b, float a) = 0;

    virtual void setDepthStencilState(const DepthStencilState& depthStencilState) = 0;

    virtual void setClearAction(unsigned int action) = 0;

    virtual void setClearColor(float r, float g, float b, float a) = 0;

    virtual void setShader(Shader * shader) = 0;

    virtual void bindVertexBuffer(unsigned int bufferID) = 0;

    virtual void drawArrays(int first, int numVertex) = 0;

    virtual ~RenderContext() {};

private:

};


NAMESPACE_END

