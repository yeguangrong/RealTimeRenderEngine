#pragma once

#include<Base/Constants.h>
#include <mutex>

NAMESPACE_START

class Shader;

struct DepthStencilState {
    bool depthTest = true;
    bool depthWrite = true;
};

class RenderContext
{

protected:
    static RenderContext* instance;
    RenderContext() {};

public:

    void setCurrentRenderContext(RenderContext* renderContext) {
        instance = renderContext;
    };

    static RenderContext* getInstance() {
        return instance;
    }


    virtual void setClearColor(float r, float g, float b, float a) = 0;

    virtual void setDepthStencilState(const DepthStencilState& depthStencilState) = 0;

    virtual void setClearAction(unsigned int action) = 0;

    virtual void setShader(Shader * shader) = 0;

    virtual void bindVertexBuffer(unsigned int bufferID) = 0;

    virtual unsigned int createVertexBuffer(const void * data, int sizeInByte) = 0;

    virtual unsigned int createVertexBufferLayoutInfo(unsigned int vertexBufferID) = 0;

    virtual void setUpVertexBufferLayoutInfo(unsigned int vertexBufferID, unsigned int vertexBufferLayoutID, int size, int stride, int location, int offset = 0) = 0;

    virtual void drawArrays(int first, int numVertex) = 0;

    virtual ~RenderContext() {};

private:

};


NAMESPACE_END

