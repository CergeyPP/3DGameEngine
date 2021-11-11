#pragma once
#include "Pawn.h"
class Player :
	public Pawn
{
public :

	Player(glm::vec3 pos, glm::vec3 a = glm::vec3(0)) : Pawn(pos, a, NULL) {

	}

	void update(float time) override;

private:

	
};

