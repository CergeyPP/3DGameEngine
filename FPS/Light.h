#pragma once
#include "Object.h"

struct LightMaterial {
	glm::vec3 diffuse;
	glm::vec3 specular;

	LightMaterial(glm::vec3 = glm::vec3(1.f), glm::vec3 = glm::vec3(1.f));
};

class Light : public Object {
public:

	Light(glm::vec3 Color, float Strength = 1.f, glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL)
		: Object(pos, angle, parent){

		scene->lights.push_back(this);
		color = Color;
		strength = Strength;
	}
	glm::vec3 getColor() {
		return color;
	}
	float getLightStrength() {
		return strength;
	}

	virtual bool setupLight(GLuint shader) = 0;

	LightMaterial material;

protected:

	glm::vec3 color;
	float strength;
};