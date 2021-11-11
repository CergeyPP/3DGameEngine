#pragma once
#include "Actor.h"
#include "Skeleton.h"

enum pawnSkeletonType {
	pawnSkeletonLEGS = 0,
	pawnSkeletonBODY = 1,
	pawnSkeletonARM_LEFT = 2,
	pawnSkeletonARM_RIGHT = 3,
};

enum pawnAttachObjectType {
	pawnAttachObjectLEFT_HAND = 0,
	pawnAttachObjectRIGHT_HAND = 1,
	pawnAttachObjectHEAD = 2,
};

class Pawn : public Actor{
public:

	Pawn(glm::vec3 pos, glm::vec3 angle = glm::vec3(0), Object* parent = NULL);
	
	Skeleton* getSkeletonPart(pawnSkeletonType partType) {
		return &skeletonParts[partType];
	}

	void update(float seconds) override;

	Object* getAttachObject(pawnAttachObjectType);

protected:

	Skeleton skeletonParts[4];
	Object headNode;

	Object* attachObjects[3];
};

