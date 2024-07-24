#include "BasePassRenderer.h"
#include"Base/ShaderCode.h"
#include"Base/Shader.h"
#include"Base/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"RenderGraph/RenderGraph.h"

NAMESPACE_START

BasePassRenderer::BasePassRenderer() {

    depthStencilState.depthTest = true;

    RenderContext* renderContext = RenderContext::getInstance();
    if (!renderContext) {
        return;
    }

    lightingShader = new Shader(Vertbasic_lighting, Fragbasic_lighting);
    lightingShader->ref();
    
    lightCubeShader = new Shader(Vertlight_cube, Fraglight_cube);
    lightCubeShader->ref();

    if (!VBO) {
        VBO = renderContext->createVertexBuffer(vertices, sizeof(vertices));
    }
    if (!cubeVAO) {
        cubeVAO = renderContext->createVertexBufferLayoutInfo(VBO);
        renderContext->setUpVertexBufferLayoutInfo(VBO, cubeVAO, 3, 6 * sizeof(float), 0, 0);
        renderContext->setUpVertexBufferLayoutInfo(VBO, cubeVAO, 3, 6 * sizeof(float), 1, 3);
    }
    if (!lightCubeVAO) {
        lightCubeVAO = renderContext->createVertexBufferLayoutInfo(VBO);
        renderContext->setUpVertexBufferLayoutInfo(VBO, lightCubeVAO, 3, 6 * sizeof(float), 0, 0);
    }
    
}

void BasePassRenderer::render(Camera* camera, RenderGraph & rg){

    const char* passName = "basePass";
    
    rg.addPass(passName, camera,
        [this, camera](RenderContext * renderContext) {
        
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        // render
           // ------
        renderContext->setDepthStencilState(depthStencilState);
        renderContext->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        renderContext->setClearAction(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader->use();
        lightingShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader->setVec3("lightPos", lightPos);
       
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        lightingShader->setMat4("projection", projection);
        lightingShader->setMat4("view", view);
       
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader->setMat4("model", model);
       
        // render the cube
        renderContext->bindVertexBuffer(cubeVAO);
        renderContext->drawArrays(0, 36);
       
        // also draw the lamp object
        lightCubeShader->use();
        lightCubeShader->setMat4("projection", projection);
        lightCubeShader->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader->setMat4("model", model);
       
        renderContext->bindVertexBuffer(lightCubeVAO);
        renderContext->drawArrays(0, 36);
    
    });
}

BasePassRenderer::~BasePassRenderer() {

    if (lightingShader && lightingShader->unref()) {
        delete lightingShader;
    }
    lightingShader = nullptr;
    
    if (lightCubeShader && lightCubeShader->unref()) {
        delete lightCubeShader;
    }
    lightCubeShader = nullptr;
    
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

NAMESPACE_END



