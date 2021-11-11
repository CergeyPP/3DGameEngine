#include "Skeleton.h"
#include "Bone.h"
#include "Texture.h"
#include <iostream>
#include "Mesh.h"

std::vector<Bone*>* Skeleton::getBones() {
	return &bones;
}

void Skeleton::update(float seconds) {
	deltaTime += seconds;
}

Skeleton::Skeleton(glm::vec3 pos, glm::vec3 angle, Object* parent) 
	: Actor(pos, angle, parent) {

	animStatys = 0;
	poseIndex = 0;
	deltaTime = 0;
}

glm::mat4 Skeleton::getAnimationMatrix(int boneID) {

	AnimationBoneTransform transform;

	float k = deltaTime / animPatterns[animStatys].pose[poseIndex].time;

	//std::cout << k << std::endl;

	while (k >= 1.f) {
		deltaTime -= animPatterns[animStatys].pose[poseIndex].time;

		poseIndex++;
		if (poseIndex > animPatterns[animStatys].pose.size() - 1) {
			poseIndex = 0;
		}

		k = deltaTime / animPatterns[animStatys].pose[poseIndex].time;
	}

	int nextPoseIndex = poseIndex + 1;
	if (nextPoseIndex > animPatterns[animStatys].pose.size() - 1) {
		nextPoseIndex = 0;
	}

	transform.transform = animPatterns[animStatys].pose[poseIndex].bone[boneID].transform + 
		+ k * (animPatterns[animStatys].pose[nextPoseIndex].bone[boneID].transform - animPatterns[animStatys].pose[poseIndex].bone[boneID].transform);

	transform.rotation = animPatterns[animStatys].pose[poseIndex].bone[boneID].rotation +
		+ k * (animPatterns[animStatys].pose[nextPoseIndex].bone[boneID].rotation - animPatterns[animStatys].pose[poseIndex].bone[boneID].rotation);

	glm::mat4 r = glm::mat4_cast(glm::quat(transform.rotation));
	glm::mat4 t(1.f);
	t = glm::translate(t, transform.transform);

	//return glm::scale(t * r, glm::vec3(0.5));
	return t * r;
}
