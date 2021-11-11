#pragma once
#include "Actor.h"

class CameraInputObject : public Actor {
public:

	void update(float sec) override;
	CameraInputObject(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL)
		: Actor(pos, angle, parent) {
	
	}



};
