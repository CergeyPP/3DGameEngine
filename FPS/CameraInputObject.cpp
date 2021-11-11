#include "CameraInputObject.h"
#include "Input.h"
#include <iostream>

void CameraInputObject::update(float sec) {

	sec *= 3;

	if (Input::keyPressed[GLFW_KEY_UP]) {

		glm::vec3 pos = glm::vec3(0);

		pos.x += cosf(angle.y) * cosf(angle.z) * sec;
		pos.y += sinf(angle.z) * sec;
		pos.z += sinf(-angle.y) * cosf(angle.z) * sec;

		m_vector += pos;
	}
	if (Input::keyPressed[GLFW_KEY_DOWN]) {

		glm::vec3 pos = glm::vec3(0);

		pos.x -= cosf(angle.y) * cosf(angle.z) * sec;
		pos.y -= sinf(angle.z) * sec;
		pos.z -= sinf(-angle.y) * cosf(angle.z) * sec;

		m_vector += pos;
	}
	if (Input::keyPressed[GLFW_KEY_RIGHT]) {
		glm::vec3 pos = glm::vec3(0);

		pos.x -= cosf(angle.y + glm::radians(90.f)) * sec;
		pos.z -= sinf(-angle.y - glm::radians(90.f)) * sec;

		m_vector += pos;
	}
	if (Input::keyPressed[GLFW_KEY_LEFT]) {
		glm::vec3 pos = glm::vec3(0);

		pos.x += cosf(angle.y + glm::radians(90.f)) * sec;
		pos.z += sinf(-angle.y - glm::radians(90.f)) * sec;

		m_vector += pos;
	}

	angle.y -= glm::radians(Input::mouseOffsetX * 3.14 * 7.f / float(WIDTH));
	angle.z -= glm::radians(Input::mouseOffsetY * 3.14 * 7.f / float(HEIGHT));

}