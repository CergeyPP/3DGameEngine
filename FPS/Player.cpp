#include "Player.h"
#include "Input.h"
#include <iostream>
#include <stdio.h>
#include "Bone.h"

void Player::update(float sec) {

	bool movF = 0;

	float movespeed = 10;

	sec *= movespeed;

	glm::vec3 m_vector = glm::vec3(0);

	if (Input::keyPressed[GLFW_KEY_W]) {

		movF = 1;
		m_vector += glm::vec3(cosf(angle.y), 0, sinf(-angle.y)) * sec;
		skeletonParts[pawnSkeletonLEGS].animStatys = 1;
		skeletonParts[pawnSkeletonBODY].animStatys = 1;
	}
	if (Input::keyPressed[GLFW_KEY_S]) {

		m_vector += glm::vec3(-cosf(angle.y), 0, -sinf(-angle.y)) * sec;

		movF = 1;
		skeletonParts[pawnSkeletonLEGS].animStatys = 1;
		skeletonParts[pawnSkeletonBODY].animStatys = 1;
	}
	if (Input::keyPressed[GLFW_KEY_A]) {

		movF = 1;
		m_vector += glm::vec3(cosf(angle.y + glm::radians(90.f)), 0, sinf(-angle.y - glm::radians(90.f))) * sec;
		skeletonParts[pawnSkeletonLEGS].animStatys = 1;
		skeletonParts[pawnSkeletonBODY].animStatys = 1;
	}
	if (Input::keyPressed[GLFW_KEY_D]) {

		movF = 1;
		m_vector += glm::vec3(-cosf(angle.y + glm::radians(90.f)), 0, -sinf(-angle.y - glm::radians(90.f))) * sec;
		skeletonParts[pawnSkeletonLEGS].animStatys = 1;
		skeletonParts[pawnSkeletonBODY].animStatys = 1;
	}

	if (movF == 0) {
		skeletonParts[pawnSkeletonLEGS].animStatys = 0;
		skeletonParts[pawnSkeletonBODY].animStatys = 0;

		skeletonParts[pawnSkeletonLEGS].poseIndex = 0;
		skeletonParts[pawnSkeletonBODY].poseIndex = 0;
	}

	//rotate(glm::quat(glm::vec3(glm::radians(Input::mouseOffsetX * 3.14 * 7.f / float(WIDTH)), -glm::radians(Input::mouseOffsetY * 3.14 * 7.f / float(HEIGHT)), 0)));
	rotate(glm::vec3(0, -glm::radians(Input::mouseOffsetX * 3.14 * 7.f / float(WIDTH)), 0));

	//glm::vec3 rotation = angle + glm::vec3(0, glm::radians(Input::mouseOffsetX * 3.14 * 7.f / float(WIDTH)), 0);
	
	/*if (rotation.y > 3.14) {
		rotation.y -= 2 * 3.14;
	}
	if (rotation.y < -3.14) {
		rotation.y += 2 * 3.14;
	}*/

	//setRotate(rotation);

	glm::vec3 rotation = glm::vec3(0, 0, -glm::radians(Input::mouseOffsetY * 3.14 * 7.f / float(HEIGHT)) );
	//rotation += getAttachObject(pawnAttachObjectHEAD)->getRot();
	/*if (rotation.z > 3.14 / 2) {
		rotation.z = 3.14 / 2;
	}
	if (rotation.z < -3.14 / 2) {
		rotation.z = -3.14 / 2;
	}*/
	//rotation -= getAttachObject(pawnAttachObjectHEAD)->getRot();

	headNode.rotate(rotation);
	
	skeletonParts[pawnSkeletonARM_LEFT].getBones()->at(0)->rotate(rotation);
	skeletonParts[pawnSkeletonARM_RIGHT].getBones()->at(0)->rotate(rotation);
	//getAttachObject(pawnAttachObjectRIGHT_HAND)->rotate(rotation);

	this->m_vector += m_vector;

	Pawn::update(sec);
}