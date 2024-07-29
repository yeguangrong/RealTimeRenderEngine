#include "BasePassRenderer.h"
#include"Base/ShaderCode.h"
#include"Base/Shader.h"
#include"Base/Camera.h"
#include"Base/Mesh.h"

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

    mesh = new Mesh();
    glm::vec3* vertex = new glm::vec3[3]{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f) , glm::vec3(0.5f,  0.5f, -0.5f) };
    glm::vec3* normal = new glm::vec3[3]{ glm::vec3(0.0f,  0.0f, 1.0f), glm::vec3(0.0f,  0.0f, 1.0f) , glm::vec3(0.0f,  0.0f, 1.0f) };

    mesh->createVertextBuffer(3, vertex, normal, nullptr);

    unsigned int* indices = new unsigned int[3]{ 0,1,2 };//只有一个三角形
    mesh->createTriangleIndexBuffer(1, indices);

    lightingShader = TRefCountPtr<Shader>(new Shader(Vertbasic_lighting, Fragbasic_lighting));

    lightCubeShader = TRefCountPtr<Shader>(new Shader(Vertlight_cube, Fraglight_cube));
    
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

        renderContext->bindVertexBuffer(mesh->vertexAttributeBufferID);

        renderContext->bindIndexBuffer(mesh->indexBufferID);
        //renderContext->drawArrays(0, 3);
        renderContext->drawElements(mesh->numTriangle * 3, 0);
    
    });
}

BasePassRenderer::~BasePassRenderer() {
    

}

NAMESPACE_END



