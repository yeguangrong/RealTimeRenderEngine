#include "MeshRenderer.h"
#include "Base/ShaderCode.h"
#include "Base/Shader.h"
#include "Base/Camera.h"
#include "RenderGraph/RenderGraph.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

NAMESPACE_START
MeshRenderer::MeshRenderer(const std::string& modelPath) {
    depthStencilState.depthTest = true;
    modelSample = new Model(modelPath);
 
    lightingShader = TRefCountPtr<Shader>(new Shader(Vertmodel_lighting, Fragmodel_lighting));
    textureMap["Hand"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/hand_dif.png");
    textureMap["Glass"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/glass_dif.png");
    textureMap["Body"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/body_dif.png");
    textureMap["Helmet"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/helmet_diff.png");
    textureMap["Leg"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/leg_dif.png");
    textureMap["Arm"] = RenderContext::getInstance()->loadTexture2D("E:/learnRenderC++/resources/objects/nanosuit/arm_dif.png");

}

void MeshRenderer::render(Camera* camera, RenderGraph& rg) {
    const char* passName = "modelPass";

    rg.addPass(passName, camera, [this, camera](RenderContext* renderContext) {
        renderContext->setDepthStencilState(depthStencilState);

     //   renderContext->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        renderContext->setClearAction(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int errorCode = glGetError();
        lightingShader.getPtr()->use();
        errorCode = glGetError();
        glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
       
        float radius = 2.0f; // 设置光源旋转半径
        lightPos.x = lightPos.x+radius * cos(time);
        lightPos.z = lightPos.z+radius * sin(time);
 

        lightingShader.getPtr()->setVec3("objectColor", 1.0f, 0.8f, 0.71f);
        lightingShader.getPtr()->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.getPtr()->setVec3("lightPos", lightPos);

        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.getPtr()->setMat4("projection", projection);

        glm::mat4 view = camera->GetViewMatrix();
        lightingShader.getPtr()->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.getPtr()->setMat4("model", model);

        lightingShader.getPtr()->setInt("baseTexture", 0);

        for (const Mesh* mesh : modelSample->meshes) {
            Texture2D* baseTexture = textureMap["Default"];
            if (textureMap.find(mesh->nowName) != textureMap.end()) {
                baseTexture = textureMap[mesh->nowName];
            }
            else {
                baseTexture = nullptr;
            }
            // 绑定纹理
            renderContext->bindTexture(baseTexture->id, 0);
            // 清除之前绑定的纹理和缓冲区
            renderContext->bindVertexBuffer(0);
            renderContext->bindIndexBuffer(0);

            // 设置纹理和缓冲区
            if (baseTexture) {
                renderContext->bindTexture(baseTexture->id, 0);
            }
            renderContext->bindVertexBuffer(mesh->vertexAttributeBufferID);
            renderContext->bindIndexBuffer(mesh->indexBufferID);

            // 渲染当前网格
            renderContext->drawElements(mesh->numTriangle * 3, 0);
        }
        renderContext->bindVertexBuffer(0);
        renderContext->bindIndexBuffer(0);
        });
}

MeshRenderer::~MeshRenderer() {
  
    delete modelSample;
}
NAMESPACE_END