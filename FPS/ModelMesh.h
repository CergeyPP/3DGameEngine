#pragma once
#include "Mesh.h"
#include <string>
#include <vector>

struct Texture {
	GLuint id;
	std::string type;
};

class ModelMesh{
public:

	void draw(GLuint shader);
	ModelMesh(std::vector<Vertex>, std::vector<unsigned int>, std::vector<Texture>, Material material = Material());

	Material material;

	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

private:

	GLuint VBO, VAO, EBO;
	void setup();

};

