#pragma once
#include "Mesh.h"
#include "ModelMesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp/postprocess.h>
#include <assimp\texture.h>

class Model : public Mesh {
public:

	Model(std::string way, glm::vec3 scale = glm::vec3(1), glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL) 
		: Mesh(pos, angle, parent){

		loadModel(way, scale);
	}
	void Draw() override;

private:

	std::vector<ModelMesh> meshes;
	std::string path;

	void loadModel(std::string, glm::vec3 scale);
	void processNode(aiNode* node, const aiScene* scene, glm::vec3 scale);
	ModelMesh processMesh(aiMesh* mesh, const aiScene* scene, glm::vec3 scale);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

