#include "Bone.h"
#include "Skeleton.h"
#include <glm/gtc/quaternion.hpp>
#include <iostream>

glm::mat4 Bone::getTransformMatrix() {

	glm::mat4 transformMatrix = glm::mat4(1.f);
	transformMatrix = glm::translate(transformMatrix, pos);
	transformMatrix = transformMatrix * glm::mat4_cast(glm::quat(angle));

	glm::mat4 transformM = transformMatrix * skeleton->getAnimationMatrix(boneID);

	return getBasicObject()->getTransformMatrix() * transformM;
}


Bone::Bone(Skeleton* skelet, Object* parent, glm::vec3 pos, glm::vec3 angle)
	: Object(pos, angle, (parent == NULL) ? skelet : parent){

	skeleton = skelet;

	boneID = skelet->getBones()->size();
}