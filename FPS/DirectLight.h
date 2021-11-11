#pragma once
#include "Light.h"

class DirectLight : public Light {
public:

	bool setupLight(GLuint shader) override;
	DirectLight(glm::vec3 color, glm::vec3 direction = glm::vec3(0, 0, glm::radians(90.f)), float strength = 1, Object* parent = NULL);

	~DirectLight() override {};

};