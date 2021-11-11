#pragma once
#include "Object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera : public Object {
public:

	Camera(GLFWwindow* win, glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL, float Fov = glm::radians(45.f));
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	glm::vec3 getViewPosOnCurrentFrame();

	~Camera() override {};

private:

	glm::vec3 viewPosOnLastFrame;
	GLFWwindow* window;
	float FOV;

};