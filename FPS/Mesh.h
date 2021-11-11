#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Texture.h"
#include <algorithm>

struct Material {
	GLuint diffuse = 0;
	GLuint specular = 0;
	float shininess = 32;

	void setSpecularColor(glm::vec3 spec) {
		
		specular = generateTextureFromColor(spec);
	}

	void setDiffuseColor(glm::vec3 diff) {

		diffuse = generateTextureFromColor(diff);
	}

	Material(GLuint pathDiffuse = 0, GLuint pathSpecular = 0) {
		if (pathDiffuse == 0) {
			setDiffuseColor(glm::vec3(1));
		}
		else
			diffuse = pathDiffuse;
		if (pathSpecular == 0) {
			setSpecularColor(glm::vec3(1));
		}
		else
			specular = pathSpecular;
	}
	Material(glm::vec3 Diffuse, glm::vec3 Specular) {
		setSpecularColor(Specular);
		setDiffuseColor(Diffuse);
	}
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;

	Vertex(glm::vec3 Position = glm::vec3(0), glm::vec3 Normal = glm::vec3(0), glm::vec2 TexCoords = glm::vec2(0)) {
		position = Position;
		normal = Normal;
		texCoords = TexCoords;
	}
};



class Mesh : public Object{
public:

	virtual void Draw();
	std::vector<Vertex>* getVerticesVector();
	GLuint* getTexture();

	Mesh(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL);
	~Mesh() override {
		scene->meshes.erase(std::find(scene->meshes.begin(), scene->meshes.end(), this));
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}

	Material material;

	ShaderType getRenderShaderType() {
		return renderShaderType;
	}
	void setRenderShaderType(ShaderType type) {
		renderShaderType = type;
	}

protected:

	std::vector<Vertex> vertices;
	ShaderType renderShaderType;
	GLuint VAO, VBO, EBO;

	virtual void setup();

	friend void setCube(Mesh*, glm::vec3, glm::vec3, GLuint);

};

void setCube(Mesh* mesh, glm::vec3 sides, glm::vec3 color, GLuint texture = GLuint(0));
