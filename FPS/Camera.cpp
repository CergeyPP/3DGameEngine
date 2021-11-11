#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

glm::mat4 Camera::getViewMatrix() {

	glm::mat4 transformMatrix = getTransformMatrix();

	glm::vec3 pos = transformMatrix * glm::vec4(0, 0, 0, 1);
	/*glm::vec3 angle = glm::eulerAngles(glm::quat(transformMatrix));
	transformMatrix = glm::translate(glm::mat4(1), pos) * glm::mat4_cast(glm::quat(angle));*/
	//std::cout << "CamAngle: " << angle.x << " " << angle.y << " " << angle.z << std::endl;
	/*

	

	angle.y *= -1;

	glm::vec3 lookDirect = glm::vec3(cosf(angle.y) * cosf(angle.z), sinf(angle.z), sinf(angle.y) * cosf(angle.z));

	if (fabsf(angle.x) >= glm::radians(179.f)) {
		lookDirect.z *= -1;
		lookDirect.y *= -1;
	}*/

	glm::vec3 target = transformMatrix * glm::vec4(1, 0, 0, 1);

	viewPosOnLastFrame = pos;

	return glm::lookAt(pos, target, glm::vec3(0, 1, 0));

}


glm::mat4 Camera::getProjectionMatrix() {

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	return glm::perspective(FOV, (float)width / (float)height, 0.01f, 600.f);
}

Camera::Camera(GLFWwindow* win, glm::vec3 pos, glm::vec3 angle, Object* parent, float Fov)
	: Object(pos, angle, parent) {

	FOV = Fov;
	window = win;
	getScene()->cameras.push_back(this);
}

glm::vec3 Camera::getViewPosOnCurrentFrame() {
	return viewPosOnLastFrame;
}