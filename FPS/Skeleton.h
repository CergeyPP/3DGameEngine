#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AnimationPoseBone.h"
#include "Actor.h"

class Bone;

class Skeleton : public Actor{
public:

	std::vector<Bone*>* getBones();
	Skeleton(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL);
	glm::mat4 getAnimationMatrix(int boneID);

	int getAnimationStatys() {
		return animStatys;
	}

	void update(float seconds) override;

protected:

	std::vector<Bone*> bones;
	std::vector<Animation> animPatterns;

	int animStatys, poseIndex;
	float deltaTime;

	friend class Pawn;
	friend class Bot;
	friend class Player;
};



