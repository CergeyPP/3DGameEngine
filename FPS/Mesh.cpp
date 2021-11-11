#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include <iostream>
#include "Light.h"
#include "Camera.h"

//std::vector<GLuint> texs;

void Mesh::Draw() {

	if (!scene->shaderCollector.isShaderExists(renderShaderType)) return;

	GLuint shader = scene->shaderCollector.getShader(renderShaderType);

	glUseProgram(shader);

	glm::mat4 transform = getTransformMatrix();
	GLuint transformLoc = glGetUniformLocation(shader, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE , &transform[0][0]);

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

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::vector<Vertex>* Mesh::getVerticesVector() {
	return &vertices;
}

GLuint* Mesh::getTexture() {
	return &material.diffuse;
}

void Mesh::setup(/*GLuint tex*/) {

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	
	//std::cout << &textures << " textures\n";
		
}

void setCube(Mesh* mesh, glm::vec3 sides, glm::vec3 color, GLuint texture){

	glm::vec3 side(fabsf(sides.x), fabsf(sides.y), fabsf(sides.z));

	float texY = side.y / (side.y + 2 * side.z);
	float texX = side.x / (2 * (side.x + side.z));
	float texZ_w = side.z / (2 * (side.x + side.z));
	float texZ_h = side.z / (2 * side.z + side.y);

	mesh->material.diffuse = texture;
	if (texture == 0) {
		mesh->material.setDiffuseColor(color);
	}
	mesh->material.shininess = 32.f;

	std::vector<Vertex> vertices = {
					
		Vertex(glm::vec3(1, 0, 0),		glm::vec3(0,0,-1),		glm::vec2(texX, texY)),					//
		Vertex(glm::vec3(0, 0, 0),		glm::vec3(0,0,-1),		glm::vec2(0, texY)),					//			это
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(0,0,-1),		glm::vec2(0, 0)),						//			левая( -z )
																										//
		Vertex(glm::vec3(1, 0, 0),		glm::vec3(0,0,-1),		glm::vec2(texX, texY)),					//			грань
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(0,0,-1),		glm::vec2(0, 0)),						//			куба
		Vertex(glm::vec3(1, 1, 0),		glm::vec3(0,0,-1),		glm::vec2(texX, 0)),					//

		Vertex(glm::vec3(1, 1, 0),		glm::vec3(1,0,0),		glm::vec2(texX + texZ_w, 0)),			//
		Vertex(glm::vec3(1, 1, 1),		glm::vec3(1,0,0),		glm::vec2(texX, 0)),					//			это 
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(1,0,0),		glm::vec2(texX, texY)),					//			передняя( +x )
																										//			грань		
		Vertex(glm::vec3(1, 0, 0),		glm::vec3(1,0,0),		glm::vec2(texX + texZ_w, texY)),		//
		Vertex(glm::vec3(1, 1, 0),		glm::vec3(1,0,0),		glm::vec2(texX + texZ_w, 0)),			//			куба
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(1,0,0),		glm::vec2(texX, texY)),					//

		Vertex(glm::vec3(1, 1, 1),		glm::vec3(0,0,1),		glm::vec2(2 * texX + texZ_w, 0)),		//
		Vertex(glm::vec3(0, 1, 1),		glm::vec3(0,0,1),		glm::vec2(texX + texZ_w, 0)),			//			это
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(0,0,1),		glm::vec2(2 * texX + texZ_w, texY)),	//			правая( +z )
																										//
		Vertex(glm::vec3(0, 1, 1),		glm::vec3(0,0,1),		glm::vec2(texX + texZ_w, 0)),			//			грань
		Vertex(glm::vec3(0, 0, 1),		glm::vec3(0,0,1),		glm::vec2(texX + texZ_w, texY)),		//			куба
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(0,0,1),		glm::vec2(2 * texX + texZ_w, texY)),	//
				
		Vertex(glm::vec3(0, 1, 1),		glm::vec3(-1,0,0),		glm::vec2(1, 0)),						//
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(-1,0,0),		glm::vec2(1 - texZ_w, 0)),				//			это
		Vertex(glm::vec3(0, 0, 1),		glm::vec3(-1,0,0),		glm::vec2(1, texY)),					//			задняя ( -x )
																										//			грань
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(-1,0,0),		glm::vec2(1 - texZ_w, 0)),				//
		Vertex(glm::vec3(0, 0, 0),		glm::vec3(-1,0,0),		glm::vec2(1 - texZ_w, texY)),			//			куба
		Vertex(glm::vec3(0, 0, 1),		glm::vec3(-1,0,0),		glm::vec2(1, texY)),					//

		Vertex(glm::vec3(1, 1, 0),		glm::vec3(0,1,0),		glm::vec2(texX, texY)),					//
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(0,1,0),		glm::vec2(0, texY)),					//			это
		Vertex(glm::vec3(1, 1, 1),		glm::vec3(0,1,0),		glm::vec2(texX, texY + texZ_h)),		//			верхняя ( +y )
																										//	
		Vertex(glm::vec3(0, 1, 0),		glm::vec3(0,1,0),		glm::vec2(0, texY)),					//			грань
		Vertex(glm::vec3(0, 1, 1),		glm::vec3(0,1,0),		glm::vec2(0, texY + texZ_h)),			//			куба (наложение текстуры от -z до +z)
		Vertex(glm::vec3(1, 1, 1),		glm::vec3(0,1,0),		glm::vec2(texX, texY + texZ_h)),		//

		Vertex(glm::vec3(0, 0, 0),		glm::vec3(0,-1,0),		glm::vec2(0, texY + texZ_h)),			//
		Vertex(glm::vec3(1, 0, 0),		glm::vec3(0,-1,0),		glm::vec2(texX, texY + texZ_h)),		//			это 
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(0,-1,0),		glm::vec2(texX, 1)),					//			нижняя ( -y )
																										//			грань
		Vertex(glm::vec3(0, 0, 1),		glm::vec3(0,-1,0),		glm::vec2(0, 1)),						//
		Vertex(glm::vec3(0, 0, 0),		glm::vec3(0,-1,0),		glm::vec2(0, texY + texZ_h)),			//			куба (наложение текстуры от -z до +z)
		Vertex(glm::vec3(1, 0, 1),		glm::vec3(0,-1,0),		glm::vec2(texX, 1)),					//
	};

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].position.x = vertices[i].position.x * sides.x;
		vertices[i].position.y = vertices[i].position.y * sides.y;
		vertices[i].position.z = vertices[i].position.z * sides.z;
	}
	
	/*if (texture == 0) {
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].texCoords.x = -2;
			vertices[i].texCoords.y = -2;
		}
	}*/
	
	mesh->vertices = vertices;

	//std::cout << mesh.getVerticesVector()->size() << std::endl;

	/*for (int i = 0; i < mesh.getVerticesVector()->size(); i++) {
		std::cout << mesh.getVerticesVector()->at(i) << " ";
		if ((i + 1) % 6 == 0) std::cout << std::endl;
	}*/

	//mesh.getIndicesVector()->insert(mesh.getIndicesVector()->end(), addindices.begin(), addindices.end());
	//std::cout << mesh.getIndicesVector()->size();
	mesh->setup();
}

Mesh::Mesh(glm::vec3 pos, glm::vec3 angle, Object* parent)
	: Object(pos, angle, parent)
{
	getScene()->meshes.push_back(this);
	renderShaderType = MySkeletonShader;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
