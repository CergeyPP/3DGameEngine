#include "Model.h"
#include <iostream>
#include "Texture.h"
#include <sstream>

void Model::loadModel(std::string path, glm::vec3 scale) {

	Assimp::Importer importer;
	const aiScene* Scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (Scene == NULL || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    this->path = "d:/проекты/FPS/FPS/"+path;

    processNode(Scene->mRootNode, Scene, scale);
}

void Model::processNode(aiNode* node, const aiScene* scene, glm::vec3 scale) {

    for (int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, scale));
    }

    for (int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, scale);
    }
}

ModelMesh Model::processMesh(aiMesh* mesh, const aiScene* scene, glm::vec3 scale) {

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    Material mat(glm::vec3(0), glm::vec3(0));
    mat.shininess = 0.f;

    glm::vec3 diffuse = glm::vec3(0);

    for (unsigned long long i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 pos;
        pos.x = mesh->mVertices[i].x * scale.x;
        pos.y = mesh->mVertices[i].y * scale.y;
        pos.z = mesh->mVertices[i].z * scale.z;
        vertex.position = pos;

        glm::vec3 normal;
        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;
        vertex.normal = normal;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 texCoord(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            vertex.texCoords = texCoord;
        }
        else vertex.texCoords = glm::vec2(0, 0);

		vertices.push_back(vertex);
    }



    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
		if (face.mNumIndices == 3) {
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}
		/*for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);*/
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        for (int i = 0; i < material->mNumProperties; i++) {
            aiMaterialProperty* Property = material->mProperties[i];
           
            std::string propertyName = Property->mKey.C_Str();
            
            if (propertyName[0] == '?') continue;
            propertyName.erase(0, 1);
            std::string type = std::string(propertyName.begin(), propertyName.begin() + propertyName.find('.'));
            //std::cout << type << " ";
            propertyName.erase(0, type.size() + 1);
           // std::cout << propertyName << " " << std::endl;

            if (type == "mat") {
                if (propertyName == "shininess") {
                   /* mat.shininess = float(*Property->mData);

                    std::cout << "shininess: " << mat.shininess << std::endl;*/

                    std::stringstream buff;

                    for (int i = 0; i < Property->mDataLength; i++) {
                        buff << Property->mData[i];
                    }

                    buff >> mat.shininess;
                }
                else if (propertyName == "opacity") {
                    // set material.opacity then it will realize
                }
            }
            else if (type == "clr") {
                if (propertyName == "transparent") {
                    // transparent = 1 - opacity;
                }
                else if (propertyName == "ambient" || propertyName == "diffuse") {

                    std::stringstream buff;

                    for (int i = 0; i < Property->mDataLength; i++) {
                        buff << Property->mData[i];
                        //std::cout << float(Property->mData[i]);
                    }
                    float r, g, b;
                    buff.read((char*)&r, Property->mDataLength / 3);
                    buff.read((char*)&g, Property->mDataLength / 3);
                    buff.read((char*)&b, Property->mDataLength / 3);

                    //std::cout << "ambient of diffuse: " << r << ":" << g << ":" << b << std::endl;

                    diffuse += glm::vec3(r, g, b);
                } 
                else if (propertyName == "specular") {
                    std::stringstream buff;

                    for (int i = 0; i < Property->mDataLength; i++) {
                        buff << Property->mData[i];
                        //std::cout << float(Property->mData[i]);
                    }
                    float r, g, b;
                    buff.read((char*)&r, Property->mDataLength / 3);
                    buff.read((char*)&g, Property->mDataLength / 3);
                    buff.read((char*)&b, Property->mDataLength / 3);

                    //std::cout << "specular: " << r << ":" << g << ":" << b << std::endl;

                    mat.setSpecularColor(glm::vec3(r, g, b));
                }
            }
        }

		//std::cout << "material n: " << material->GetName().C_Str() << std::endl;

		//aiColor4D diff;
		//if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diff) == AI_SUCCESS) {

		//	GLuint texture = generateTextureFromColor(glm::vec3(diff.r, diff.g, diff.b));
		//	Texture diffuse;
		//	diffuse.id = texture;
		//	diffuse.type = "diffuse";
		//	textures.push_back(diffuse);
		//}

		//aiColor4D spec;
  //      if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &spec) == AI_SUCCESS) {

  //          glm::vec3 color = glm::vec3(spec.r, spec.g, spec.b);
  //          /*if (color != glm::vec3(0)) {*/

  //              GLuint texture = generateTextureFromColor(color);
  //              Texture specular;
  //              specular.id = texture;
  //              specular.type = "specular";
  //              textures.push_back(specular);

  //              std::cout << "specs material: " << spec.r << " " << spec.g << " " << spec.b << " " << spec.a << std::endl;
  //          /*}
  //          else {
  //              GLuint texture = this->material.specular;
  //              Texture specular;
  //              specular.id = texture;
  //              specular.type = "specular";
  //              textures.push_back(specular);
  //          }*/

  //      }


        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        //aiString str;

        //if (material->GetTexture(aiTextureType_DIFFUSE, 0, &str) == AI_SUCCESS) {

        //    std::cout << "aeeee" << std::endl;

        //    Texture texture;
        //    GLuint tx;
        //    if (loadTexture(&tx, str.C_Str()) != 0) {
        //        std::cout << "Cant load " << str.C_Str() << std::endl;
        //        tx = 0;
        //    }
        //    texture.id = tx;
        //    texture.type = "diffuse";
        //    //texture.path = str;
        //    textures.push_back(texture);
        //}

        if (diffuseMaps.size() == 0) {
            mat.setDiffuseColor(diffuse);

            Texture texture;
            texture.id = mat.diffuse;
            texture.type = "diffuse";
            textures.push_back(texture);
        }
        if (specularMaps.size() == 0) {
            Texture texture;

            texture.id = mat.specular;
            texture.type = "specular";
            textures.push_back(texture);
        }

    }

	//std::cout << "Count of textures: " << textures.size() << std::endl;

    return ModelMesh(vertices, indices, textures, mat);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    //std::cout << "Loading" << std::endl;

    std::vector<Texture> textures;
    for (unsigned int i = 0; i < aiGetMaterialTextureCount(mat, type); i++)
    {
        //std::cout << "aeeee" << std::endl;
        
        aiString str;

        aiGetMaterialTexture(mat,type, i, &str);
        Texture texture;
        GLuint tx;
        if (loadTexture(&tx, str.C_Str()) != 0) {
            std::cout << "Cant load " << str.C_Str() << std::endl;
            tx = 0;
        }
        texture.id = tx;
        texture.type = typeName;
        //texture.path = str;
        textures.push_back(texture);
    }
    return textures;
}

void Model::Draw() {

    if (!scene->shaderCollector.isShaderExists(renderShaderType)) return;

    GLuint shader = scene->shaderCollector.getShader(renderShaderType);

    glUseProgram(shader);

    glm::mat4 transform = getTransformMatrix();
    GLuint transformLoc = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);

    GLuint diffuseLoc = glGetUniformLocation(shader, "material.diffuse");
    glUniform1i(diffuseLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.diffuse);

    GLuint specularLoc = glGetUniformLocation(shader, "material.specular");
    glUniform1i(specularLoc, 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, material.specular);

    GLuint shineLoc = glGetUniformLocation(shader, "material.shininess");
    glUniform1f(shineLoc, material.shininess);

    for (int i = 0; i < meshes.size(); i++) {
        meshes[i].draw(shader);
    }
}

