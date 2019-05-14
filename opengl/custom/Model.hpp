//
//  Model.hpp
//  LearnOpenGL
//
//  Created by 麻虾 on 17/6/4.
//
//

#ifndef Model_hpp
#define Model_hpp

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>

#include <Mesh.h>
#include <Shader.h>

//#include <glad/glad.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "PlatformUtils.h"

//#include <stb_image.h>
#include <SOIL.h>


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma=false);


class Model
{
public:
	Model(const char *ModelName)
	{
		modelName = ModelName;
		modelFilePath = common::GetModelFilePath(ModelName);
		modelDir = common::GetModelDir(ModelName);
		loadModel(modelFilePath);
	}
    void Draw(Shader &shader);
    std::vector<Mesh> meshes;
    
private:
    
	std::string modelName;
	std::string modelFilePath;
	std::string modelDir;

    std::vector<Texture> textures_loaded;
    
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
    
};

#endif /* Model_hpp */
