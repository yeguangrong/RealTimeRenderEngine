#pragma once

#include "RenderContext.h"

NAMESPACE_START

class Shader;
class Camera;

class OpenGLRenderContext : public RenderContext
{
public:

    OpenGLRenderContext();

    virtual void drawArrays(float* vextexBuffer) override;

    virtual ~OpenGLRenderContext();

    

};


NAMESPACE_END

