#include "DirectLight.h"
#include <iostream>

DirectLight::DirectLight(glm::vec3 color, glm::vec3 direction, float strength, Object* parent) 
	: Light(color, strength, glm::vec3(0), direction, parent){

}

bool DirectLight::setupLight(GLuint shader) {

	GLuint diffusePos = glGetUniformLocation(shader, "DirectLight.diffuse");
	glUniform3f(diffusePos, material.diffuse.r * color.r, material.diffuse.g * color.g, material.diffuse.b * color.b);

	GLuint specularPos = glGetUniformLocation(shader, "DirectLight.specular");
	glUniform3f(specularPos, material.specular.r * color.r, material.specular.g * color.g, material.specular.b * color.b);

	GLuint directPos = glGetUniformLocation(shader, "DirectLight.direction");
	glUniform3f(directPos, angle.x, angle.y, angle.z);

	return 1;
}