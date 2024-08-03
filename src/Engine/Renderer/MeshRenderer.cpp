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

    lightCubeShader = TRefCountPtr<Shader>(new Shader(Vertlight_cube, Fraglight_cube));
}

void MeshRenderer::render(Camera* camera, RenderGraph& rg) {
    const char* passName = "modelPass";

    rg.addPass(passName, camera, [this, camera](RenderContext* renderContext) {
        lightingShader.getPtr()->use();
        renderContext->setDepthStencilState(depthStencilState);
        renderContext->setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        renderContext->setClearAction(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingShader.getPtr()->setMat4("projection", projection);

        glm::mat4 view = camera->GetViewMatrix();
        lightingShader.getPtr()->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.getPtr()->setMat4("model", model);


        for (const Mesh& mesh : modelSample->meshes) {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            for (unsigned int i = 0; i < mesh.textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                string number;
                string name = mesh.textures[i].type;
                if (name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (name == "texture_specular")
                    number = std::to_string(specularNr++); // transfer unsigned int to string
                else if (name == "texture_normal")
                    number = std::to_string(normalNr++); // transfer unsigned int to string
                else if (name == "texture_height")
                    number = std::to_string(heightNr++); // transfer unsigned int to string

                // now set the sampler to the correct texture unit
                glUniform1i(glGetUniformLocation(lightingShader.getPtr()->ID, (name + number).c_str()), i);
                // and finally bind the texture
                glBindTexture(GL_TEXTURE_2D, mesh.textures[i].id);
            }
            renderContext->bindVertexBuffer(mesh.vertexAttributeBufferID);
            renderContext->bindIndexBuffer(mesh.indexBufferID);

            for (unsigned int i = 0; i < mesh.numTriangle; i++) {
                renderContext->drawElements(mesh.numTriangle * 3, 0);
            }
            renderContext->bindVertexBuffer(0);
            renderContext->bindIndexBuffer(0);
        }
        
        });
}

MeshRenderer::~MeshRenderer() {
    delete modelSample;
}
NAMESPACE_END