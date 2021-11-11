#pragma once
#include "Light.h"

class PointLight : public Light {
public:

	bool setupLight(GLuint shader) override;
	PointLight(glm::vec3 color, float strength, glm::vec3 pos, LightMaterial Material = LightMaterial(glm::vec3(1)), Object* parent = NULL);
		
	float linear = 0.14f;
	float quadratic = 0.07f;
};