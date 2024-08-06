#pragma once

#include<Base/Constants.h>
#include<Base/Texture2D.h>
#include <mutex>

NAMESPACE_START

class Shader;

struct DepthStencilState {
    bool depthTest = true;
    bool depthWrite = true;
};

struct FrameBuffer {
    unsigned int id = 0;
    Texture2D * colorTexture = nullptr;
    Texture2D * depthStencilTexture = nullptr;
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

    virtual Texture2D * createTexture2D(const TextureUsage& usage, const TextureFormat& textureFormat, const int width, const int height) = 0;

    virtual Texture2D * loadTexture2D(const char* path) = 0;

    virtual void bindTexture(unsigned int bufferID, unsigned int bindingIndex) = 0;

    virtual FrameBuffer createFrameBuffer() = 0;

    virtual void beginRendering(const FrameBuffer & fbo) = 0;

    virtual void endRendering() = 0;

    virtual void setClearColor(float r, float g, float b, float a) = 0;

    virtual void setDepthStencilState(const DepthStencilState& depthStencilState) = 0;

    virtual void setClearAction(unsigned int action) = 0;

    virtual void setShader(Shader * shader) = 0;

    virtual void bindVertexBuffer(unsigned int bufferID) = 0;

    virtual unsigned int createVertexBuffer(const void * data, int sizeInByte) = 0;

    virtual unsigned int createVertexBufferLayoutInfo(unsigned int vertexBufferID) = 0;

    virtual void bindIndexBuffer(unsigned int bufferID) = 0;

    virtual unsigned int createIndexBuffer(const void* data, int sizeInByte) = 0;

    virtual void setUpVertexBufferLayoutInfo(unsigned int vertexBufferID, unsigned int vertexBufferLayoutID, int size, int stride, int location, int offset = 0) = 0;

    virtual void drawArrays(int first, int numVertex) = 0;

    virtual void drawElements(unsigned int count, const void* indices) = 0;

    virtual ~RenderContext() {};

private:

};


NAMESPACE_END

