#pragma once

#include <Base/Constants.h>
#include<Base/TRefCountPtr.h>
#include <RHI/RenderContext.h>
#include "Base/Model.h" // Include Mesh and Vertex definitions
#include <unordered_map>
class RenderGraph;

NAMESPACE_START

class Camera;
class Shader;

class MeshRenderer {
public:
    MeshRenderer(const std::string& modelPath);
    ~MeshRenderer();
    float time;
    virtual void render(Camera* camera, RenderGraph& rg);

private:

    TRefCountPtr<Shader> lightingShader;
    vector< Texture2D*> textures;
    Texture2D* normalTexture = nullptr;
    DepthStencilState depthStencilState;


    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    Texture2D* baseTexture = nullptr;
    Model* modelSample = nullptr;
    unordered_map<std::string, Texture2D*> textureMap;
};

NAMESPACE_END