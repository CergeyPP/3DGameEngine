#include "ModelMesh.h"
#include <string>
#include <iostream>

ModelMesh::ModelMesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indices, std::vector<Texture> Textures, Material mat) {
	vertices = Vertices;
	indices = Indices;
	textures = Textures;
	material = mat;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	setup();
}

void ModelMesh::setup() {

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	glBindVertexArray(0);
}

void ModelMesh::draw(GLuint shader) {

	glUseProgram(shader);

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // активируем текстурный блок, до привязки
		// получаем номер текстуры
		//std::string number;
		std::string name = textures[i].type;
		//if (name == "diffuse")
		//{
		//	number += std::to_string(diffuseNr++); // передаем unsigned int в stream
		//}
		//else if (name == "specular")
		//{
		//	number += std::to_string(specularNr++); // передаем unsigned int в stream
		//}
		
		//name.erase(0, 8);
		GLuint loc = glGetUniformLocation(shader, ("material." + name).c_str());
		if (loc == -1) std::cout << "ERROR!" << std::endl;
		glUniform1f(loc, i);

		glBindTexture(GL_TEXTURE_2D, textures[i].id);

		//std::cout << "diffuse: " << diffuseNr << " ";
		//std::cout << "specular: " << specularNr << std::endl;
	}

	// отрисовывем полигональную сетку
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);

}