#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "ShaderCollector.h"

#define MAX_POINT_LIGHTS 10

class Object;
class Mesh;
class Actor;
class Camera;
class Light;
class Collider;

class Scene {
private:

	int nextPointLightIterator;

public:

	void draw();
	void update(float sec);
	void simulate();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	std::vector<Object*> objects;
	std::vector<Mesh*> meshes;
	std::vector<Actor*> actors;
	std::vector<Camera*> cameras;
	std::vector<Light*> lights;
	std::vector<Collider*> bodies;

	ShaderCollector shaderCollector;
	glm::vec3 getAmbientLightColor();
	float getAmbientLightStrength();

	Camera* activeCam;

	int	getPointLightIterator() {
		return nextPointLightIterator;
	};

	void pointLightIteratorIncrement() {
		nextPointLightIterator++;
	};

	void resetPointLightIterator() {
		nextPointLightIterator = 0;
	}
};