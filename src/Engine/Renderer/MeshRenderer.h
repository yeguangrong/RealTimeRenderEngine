#pragma once

#include <Base/Constants.h>
#include<Base/TRefCountPtr.h>
#include <RHI/RenderContext.h>
#include "Base/Model.h" // Include Mesh and Vertex definitions

class RenderGraph;

NAMESPACE_START

class Camera;
class Shader;

class MeshRenderer {
public:
    MeshRenderer(const std::string& modelPath);
    ~MeshRenderer();
    virtual void render(Camera* camera, RenderGraph& rg);

private:

    TRefCountPtr<Shader> lightingShader;
    TRefCountPtr<Shader> lightCubeShader;
    DepthStencilState depthStencilState;


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    Model* modelSample = nullptr;
};

NAMESPACE_END