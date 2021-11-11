#pragma once
#include "Object.h"

class Actor : public Object {
public:
	
	virtual void update(float seconds) = 0;
	Actor(glm::vec3 pos = glm::vec3(0), glm::vec3 angles = glm::vec3(0), Object* parent = NULL)
		: Object(pos, angles, parent) { 

		getScene()->actors.push_back(this);
	}


	~Actor() override {}

protected:

};