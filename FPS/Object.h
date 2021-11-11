#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"

class Observer;

class Object {
public:
	
	Object(glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0), Object* parent = NULL);

	virtual glm::mat4 getTransformMatrix();
	//Observer* getObserver();
	Object* getBasicObject();

	static Scene* getScene();
	static void setScene(Scene*);

	virtual ~Object() {
		
	}

	static Scene* scene;

	void setBasicObject(Object* object);
	void translate(glm::vec3 tr) {
		pos += tr;
	}
	void rotate(glm::vec3 rot) {
		angle += rot;
	}

	glm::vec3 getMoveVector() {
		return m_vector;
	}
	void setMoveVector(glm::vec3 vec) {
		m_vector = vec;
	}

protected:

	void deleteMe();

	//void pushEvent();
	glm::vec3 m_vector;
	
	glm::vec3 pos;
	glm::vec3 angle;
	Object* basicObject;
	//Observer* observer;

};







