#include "BasePassRenderer.h"
#include"Base/ShaderCode.h"
#include"Base/Shader.h"
#include"Base/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"RenderGraph/RenderGraph.h"

NAMESPACE_START

template <typename T>
struct has_preRead {
    // 使用 if constexpr 来检查 T 类型是否具有 preRead 成员函数
    static constexpr bool value = [](){
        if constexpr (std::is_same<void, decltype(std::declval<T>().preRead(
            typename T::Desc{}, 0u, std::declval<void*>())) > ::value) {
            return true;
        }
        else {
            return false;
        }
    };
};

//template <typename T>
//struct has_preRead {
//    template <typename U>
//    static constexpr std::false_type test(...) {
//        return {};
//    }
//    template <typename U>
//    static constexpr auto test(U* u) ->
//        typename std::is_same<void,
//        decltype(u->preRead(typename T::Desc{}, 0u,
//            std::declval<void*>())) > ::type {
//        return {};
//    }
//
//    static constexpr bool value{ test<T>(nullptr) };
//};

BasePassRenderer::BasePassRenderer() {

    depthStencilState.depthTest = true;

    RenderContext* renderContext = RenderContext::getInstance();
    if (!renderContext) {
        return;
    }

    lightingShader = TRefCountPtr<Shader>(new Shader(Vertbasic_lighting, Fragbasic_lighting));

    lightCubeShader = TRefCountPtr<Shader>(new Shader(Vertlight_cube, Fraglight_cube));

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
        lightingShader.getPtr()->use();
        lightingShader.getPtr()->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        lightingShader.getPtr()->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lightingShader.getPtr()->setVec3("lightPos", lightPos);
       
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        lightingShader.getPtr()->setMat4("projection", projection);
        lightingShader.getPtr()->setMat4("view", view);
       
        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.getPtr()->setMat4("model", model);
       
        // render the cube
        renderContext->bindVertexBuffer(cubeVAO);
        renderContext->drawArrays(0, 36);
       
        // also draw the lamp object
        lightCubeShader.getPtr()->use();
        lightCubeShader.getPtr()->setMat4("projection", projection);
        lightCubeShader.getPtr()->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.getPtr()->setMat4("model", model);
       
        renderContext->bindVertexBuffer(lightCubeVAO);
        renderContext->drawArrays(0, 36);
    
    });
}

BasePassRenderer::~BasePassRenderer() {
    
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
}

NAMESPACE_END



