#include "Object.h"
#include "Scene.h"

glm::mat4 Object::getTransformMatrix() {

	glm::mat4 transformMatrix = glm::mat4(1.f);
	transformMatrix = glm::translate(transformMatrix, pos);
	transformMatrix = transformMatrix * glm::mat4_cast(glm::quat(angle));

	if (basicObject == this) return transformMatrix;
	else return basicObject->getTransformMatrix() * transformMatrix;

}

//Observer* Object::getObserver() {
//	return observer;
//}

void Object::setBasicObject(Object* object) {
	basicObject = object;
}

void Object::deleteMe() {
	
}

Scene* Object::scene;

Object* Object::getBasicObject() {
	return basicObject;
}

void Object::setScene(Scene* scen) {
	scene = scen;
}

Scene* Object::getScene() {
	return (Scene*)scene;
}

Object::Object(glm::vec3 pos, glm::vec3 angle, Object* parent) {

	getScene()->objects.push_back(this);

	this->pos = pos;
	this->angle = angle;

	if (parent == NULL) parent = this;
	basicObject = parent;
}