#pragma once

#include<Base/Constants.h>

NAMESPACE_START

class Camera;

class RenderContext
{
public:

    RenderContext() {};

    virtual void prepare() {};

    virtual void render(Camera* camera) {};

    virtual ~RenderContext() {};

private:

};


NAMESPACE_END

