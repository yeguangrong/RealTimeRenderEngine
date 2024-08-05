#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include"Mesh.h"
#include"Shader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;

NAMESPACE_START
class Model {
public:
 
    std::vector<Mesh*>   meshes;
    string directory;
    bool gammaCorrection;

    Model(string const& path, bool gamma = false);
    ~Model();

private:
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);
};

NAMESPACE_END
