#include "PointLight.h"
#include <string>
#include <iostream>

PointLight::PointLight(glm::vec3 color, float strength, glm::vec3 pos, LightMaterial Material, Object* parent)
	: Light(color, strength, pos, glm::vec3(0), parent) {
	material = Material;
}

bool PointLight::setupLight(GLuint shader) {

	int lightNumber = scene->getPointLightIterator();
	if (lightNumber < MAX_POINT_LIGHTS) scene->pointLightIteratorIncrement();
	else return 0;

	std::string lightNumbToS = std::to_string(lightNumber);

	std::string loc = "PointLight[" + lightNumbToS + "].position";
	GLuint Location = glGetUniformLocation(shader, loc.c_str());
	if (Location == -1) {
		std::cout << "Cant found ";
		std::cout << loc.c_str() << std::endl;
	}
	glUniform3fv(Location, 1, &pos[0]);

	loc = "PointLight[" + lightNumbToS + "].diffuse";
	Location = glGetUniformLocation(shader, loc.c_str());
	if (Location == -1) {
		std::cout << "Cant found ";
		std::cout << loc.c_str() << std::endl;
	}
	glm::vec3 dif = material.diffuse * color;
	glUniform3fv(Location, 1, &dif[0]);

	loc = "PointLight[" + lightNumbToS + "].specular";
	Location = glGetUniformLocation(shader, loc.c_str());
	if (Location == -1) {
		std::cout << "Cant found ";
		std::cout << loc.c_str() << std::endl;
	}
	glm::vec3 spec = material.specular * color;
	glUniform3fv(Location, 1, &spec[0]);

	loc = "PointLight[" + lightNumbToS + "].linear";
	Location = glGetUniformLocation(shader, loc.c_str());
	if (Location == -1) {
		std::cout << "Cant found ";
		std::cout << loc.c_str() << std::endl;
	}
	glUniform1f(Location, linear);

	loc = "PointLight[" + lightNumbToS + "].quadratic";
	Location = glGetUniformLocation(shader, loc.c_str());
	if (Location == -1) {
		std::cout << "Cant found ";
		std::cout << loc.c_str() << std::endl;
	}
	glUniform1f(Location, quadratic);

	return 1;
}