#include "Light.h"
#include "Camera.h"

LightMaterial::LightMaterial(glm::vec3 Diffuse, glm::vec3 Specular) {
	diffuse = Diffuse;
	specular = Specular;
}