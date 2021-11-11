#pragma once
#include "Object.h"
#include "PhysicTypes.h"

class Collider {
public:

	Collider* getMe() { return this; }

	float getCollisionDetectionRadius() {
		return collisionDetectionRadius;
	}
	Collider(Object* BasicObject, float mass, float collisionDetectionR) {
		basicObject = BasicObject;
		collisionDetectionRadius = collisionDetectionR;
		Mass = mass;
		basicObject->getScene()->bodies.push_back(this);
	}
	virtual ~Collider() {}
	Object* getBasicObject() { return basicObject; }

	glm::vec3 getPosition() {
		return glm::vec3(basicObject->getTransformMatrix() * glm::vec4(0, 0, 0, 1)) + basicObject->getMoveVector();
	}

	
	void setMass(float mass) {
		Mass = mass;
	}
	float getMass() {
		return Mass;
	}

protected:

	float collisionDetectionRadius;
	float Mass;
	Object* basicObject;

};

class PlaneCollider : public Plane, Collider {
public:
	
	PlaneCollider(Object* basicObject, Plane plane) : Collider(NULL, 0, 0) ,Plane(plane){}
	virtual ~PlaneCollider() {}

private:

};

class Parallelogramm :public Collider {
public:

	Parallelogramm(Object* basicObject, float mass, glm::vec3 Offset, glm::vec3 Sides);
	virtual ~Parallelogramm() {}

	glm::vec3 offset;
	glm::vec3 sides;

	std::vector<Section> getSections();
	std::vector<Plane> getPlanes();
	std::vector<glm::vec3> getNormales();


private:

	
};

class Sphere : public Collider {

};

std::vector<glm::vec3> getCollideP(PlaneCollider a, PlaneCollider b);
std::vector<glm::vec3> getCollideP(PlaneCollider a, Sphere b);
std::vector<glm::vec3> getCollideP(PlaneCollider a, Parallelogramm b);

std::vector<glm::vec3> getCollideP(Parallelogramm a, Parallelogramm b);
std::vector<glm::vec3> getCollideP(Parallelogramm a, Sphere b);

std::vector<glm::vec3> getCollideP(Sphere a, Sphere b);