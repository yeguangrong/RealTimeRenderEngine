#pragma once

#include<Base/Constants.h>

NAMESPACE_START

class RenderContext
{
public:

    RenderContext() {};

    virtual void drawArrays(float * vextexBuffer) = 0;

    virtual ~RenderContext() {};

private:

};


NAMESPACE_END

