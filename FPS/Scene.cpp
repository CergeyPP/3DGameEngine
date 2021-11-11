#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include "Object.h"
#include "Actor.h"
#include "Light.h"
#include "Colliders.h"
#include "Input.h"
#include <iostream>
#include <memory>

struct ColliderGroup {
	Collider* mainBody;
	std::vector<Collider*> collisionBodies;
};

glm::mat4 Scene::getProjectionMatrix() {
	return activeCam->getProjectionMatrix();
}

glm::mat4 Scene::getViewMatrix() {
	return activeCam->getViewMatrix();
}

glm::vec3 Scene::getAmbientLightColor() {
	return glm::vec3(1, 1, 1);
}

float Scene::getAmbientLightStrength() {
	return 0.02f;
}

void Scene::draw() {

	nextPointLightIterator = 0;

	if (activeCam == NULL) {
		if (cameras.size() > 0)
			activeCam = cameras[0];
		else return;
	}
	/*if (Input::keyPressed[GLFW_KEY_U]) {
		if (activeCam == cameras[0]) {
			activeCam = cameras[1];
		}
		else activeCam = cameras[0];
	}*/

	for (auto shader : shaderCollector.shaders) {

		glUseProgram(shader.second);

		glm::vec3 ambient = getAmbientLightColor() * getAmbientLightStrength();
		GLuint ambientLoc = glGetUniformLocation(shader.second, "ambient");
		glUniform3f(ambientLoc, ambient.x, ambient.y, ambient.z);

		GLuint viewLoc = glGetUniformLocation(shader.second, "view");
		glm::mat4 view = getViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

		GLuint projectionLoc = glGetUniformLocation(shader.second, "projection");
		glm::mat4 projection = getProjectionMatrix();
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);

		GLuint viewPosLoc = glGetUniformLocation(shader.second, "viewPos");
		glm::vec3 viewPos = activeCam->getViewPosOnCurrentFrame();
		glUniform3f(viewPosLoc, viewPos.x, viewPos.y, viewPos.z);

		if (shader.first == SimplestShader) continue;

		for (auto l : lights) {
			l->setupLight(shader.second);
		}

		GLuint maxLightsLoc = glGetUniformLocation(shader.second, "MaxPointLight");
		glUniform1i(maxLightsLoc, getPointLightIterator());

		resetPointLightIterator();
	}

	for (auto a : meshes) {
		a->Draw();
	}

}

void Scene::update(float sec) {

	for (auto a : actors) {
		a->update(sec);
		a->translate(a->getMoveVector());
		
	}
	simulate();
	for (auto a : actors) {
		a->setMoveVector(glm::vec3(0));
	}
}

void Scene::simulate() {

	std::vector<ColliderGroup> colliderGroups;

	for (int i = 0; i < bodies.size(); i++) {
		ColliderGroup group;
		group.mainBody = bodies[i];

		glm::vec3 pos = group.mainBody->getPosition();

		for (int j = i + 1; j < bodies.size(); j++) {

			glm::vec3 bodyPos = bodies[j]->getPosition();

			float r = (group.mainBody->getCollisionDetectionRadius() + bodies[j]->getCollisionDetectionRadius()) * (group.mainBody->getCollisionDetectionRadius() + bodies[j]->getCollisionDetectionRadius());
			float delta = (pos.x - bodyPos.x) * (pos.x - bodyPos.x) + (pos.y - bodyPos.y) * (pos.y - bodyPos.y) + (pos.z - bodyPos.z) * (pos.z - bodyPos.z);
			if (delta <= r) {
				group.collisionBodies.push_back(bodies[j]);
			}
		}

		colliderGroups.push_back(group);
	}

	//std::cout << colliderGroups[0].collisionBodies.size() << std::endl;

	for (int i = 0; i < colliderGroups.size(); i++) {
		
		Parallelogramm* a = dynamic_cast<Parallelogramm*>(colliderGroups[i].mainBody);
		if (a) {
			for (int j = 0; j < colliderGroups[i].collisionBodies.size(); j++) {
				Parallelogramm* q = dynamic_cast<Parallelogramm*>(colliderGroups.at(i).collisionBodies.at(j));
				if (q) {

					if (q->getMass() > 0 && a->getMass() > 0) continue;
					bool swapF = 0;
					if (a->getMass() == 0) {
						Parallelogramm* c = a;
						a = q;
						q = c;
						swapF = 1;
					}

					//std::cout << std::endl;
					//std::cout << "yeah1!" << std::endl;

					bool f = 0;
					//glm::vec3 translateOffset = glm::vec3(0);

					std::vector<glm::vec3> points = getCollideP(*a, *q);
					
					//glm::vec3 currentPos = a->getPosition();

					//glm::vec3 offPoint = currentPos + a->sides;
					//glm::vec3 moveVec = a->getBasicObject()->getMoveVector();
					
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
						Mesh mesh(m - glm::vec3(0.1), glm::vec3(0), NULL);
						//mesh.material = Material(glm::vec3(1), glm::vec3(0));
						mesh.setRenderShaderType(SimplestShader);
						setCube(&mesh, glm::vec3(0.2), glm::vec3(1, 0, 0));

						mesh.Draw();

						
					}
					
					//For X coordinate
					//float k = 1;
					//if (moveVec.x < 0) k = -1;
					std::vector<glm::vec3> normales = q->getNormales();
					std::vector<Plane> qPlanes = q->getPlanes();
					std::vector<Section> qSec = q->getSections();

					for (int planeI = 0; planeI < qPlanes.size(); planeI++) {
						glm::vec3 p1, p2, p3, p4;
						p1 = qSec[planeI * 4].p1;
						p2 = qSec[planeI * 4].p2;
						p3 = qSec[planeI * 4 + 3].p1;
						p4 = qSec[planeI * 4 + 3].p2;

						Plane currentPlane = qPlanes[planeI];
						glm::vec3 currentNormal = normales[planeI];

						for (int xi = 0; xi < 2; xi++) {
							for (int yi = 0; yi < 2; yi++) {
								for (int zi = 0; zi < 2; zi++) {
									glm::vec3 aPoint = a->getPosition() + a->sides * glm::vec3(xi, yi, zi);
									glm::vec3 finalPoint = aPoint + a->getBasicObject()->getMoveVector();

									Line vecLine(aPoint, finalPoint);
									if (!isLineCrossPlane(currentPlane, vecLine)) continue;
									
									glm::vec3 crossPoint = getLineCrossPlane(currentPlane, vecLine);
									if (!isPointOnSection(Section(aPoint, finalPoint), crossPoint)) continue;
									if (isPointInPolygon(crossPoint, p1, p2, p3) || isPointInPolygon(crossPoint, p2, p3, p4)) {
										std::cout << "Что-то!" << std::endl;
										float distance = fabsf(currentPlane.a * finalPoint.x + currentPlane.b * finalPoint.y + currentPlane.c * finalPoint.z + currentPlane.d);
										a->getBasicObject()->translate(currentNormal * distance);
									}
								}
							}
						}
					}

					//
					a->getBasicObject()->translate(a->getBasicObject()->getMoveVector());


					//	bool planeFound = 0;
					//	glm::vec3 aPos = a->getBasicObject()->getTransformMatrix() * glm::vec4(0, 0, 0, 1);
					//	std::vector<Plane> aPlanes = a->getPlanes();
					//	std::vector<Plane> qPlanes = q->getPlanes();
					//	Line mVectorLine = Line(aPos, glm::normalize(a->getBasicObject()->getMoveVector()));

					//	Plane plane(0,0,0,0);

					//	for (int k = 0; k < 6; k++) 
					//		if (isPointOnPlane(qPlanes[k], m)) {
					//			plane = qPlanes[k];
					//		}

					//	glm::vec3 qPoint = glm::vec3(0);
					//	bool crossF = isLineCrossPlane(plane, mVectorLine);
					//	if (crossF) {
					//		qPoint = getLineCrossPlane(plane, mVectorLine);
					//	}
					//	else continue;

					//	bool offFound = 0;
					//	glm::vec3 offset;
					//	for (int k = 0; k < 6; k++) {
					//		if (getPlaneCrossLine(plane, aPlanes[k]).vec == glm::vec3(0)) {
					//			glm::vec3 aPoint = getLineCrossPlane(aPlanes[k], mVectorLine);
					//			if (offFound == 0) {
					//				offFound = 1;
					//				offset = qPoint - aPoint;
					//			}
					//			else {
					//				glm::vec3 t = (qPoint - aPoint) / mVectorLine.vec;
					//				if (t.x >= 0 && t.y >= 0 && t.z >= 0) {
					//					offset = qPoint - aPoint;
					//				}
					//			}
					//		}
					//	}

					//	if (offFound) {
					//		if (f) {
					//			float offsetSize = offset.x * offset.x + offset.y * offset.y + offset.z * offset.z;
					//			float translateSize = translateOffset.x * translateOffset.x + translateOffset.y * translateOffset.y + translateOffset.z * translateOffset.z;
					//			
					//			if (offsetSize < translateSize) {
					//				translateOffset = offset;
					//			}
					//		}
					//		else {
					//			translateOffset = offset;
					//			f = 1;
					//		}
					//	}
					//}


					////a->getBasicObject()->translate(translateOffset);
					//Mesh mesh1(a->getBasicObject()->getTransformMatrix()*glm::vec4(0,0,0,1), glm::vec3(0), NULL);
					//setCube(&mesh1, glm::vec3(0.5,0.5,0.5), glm::vec3(0, 1, 0));
					//Mesh mesh2(a->getBasicObject()->getTransformMatrix()* glm::vec4(0, 0, 0, 1) + glm::vec4(translateOffset,0), glm::vec3(0), NULL);
					//setCube(&mesh2, glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 0));

					//mesh1.Draw();
					//mesh2.Draw();

					//a->getBasicObject()->translate(translateOffset);

					if (swapF) {
						Parallelogramm* c = a;
						a = q;
						q = c;
					}
				}

				PlaneCollider* w = dynamic_cast<PlaneCollider*>(colliderGroups.at(i).collisionBodies.at(j));
				if (w) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*w, *a);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}

					a->getBasicObject()->translate(a->getBasicObject()->getMoveVector());
					a->getBasicObject()->setMoveVector(glm::vec3(0));
				}

				Sphere* e = dynamic_cast<Sphere*>(colliderGroups.at(i).collisionBodies.at(j));
				if (e) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*a, *e);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}
				}

			}

		}
		PlaneCollider* b = dynamic_cast<PlaneCollider*>(colliderGroups[i].mainBody);
		if (b) {

			for (int j = 0; j < colliderGroups[i].collisionBodies.size(); j++) {
				Parallelogramm* q = dynamic_cast<Parallelogramm*>(colliderGroups.at(i).collisionBodies.at(j));
				if (q) {
					std::cout << "yeah2!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*b, *q);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}
				}

				PlaneCollider* w = dynamic_cast<PlaneCollider*>(colliderGroups.at(i).collisionBodies.at(j));
				if (w) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*w, *b);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}
				}

				Sphere* e = dynamic_cast<Sphere*>(colliderGroups.at(i).collisionBodies.at(j));
				if (e) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*b, *e);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}
				}

			}

		}
		Sphere* c = dynamic_cast<Sphere*>(colliderGroups[i].mainBody->getMe());
		if (c) {

			for (int j = 0; j < colliderGroups[i].collisionBodies.size(); j++) {
				Parallelogramm* q = dynamic_cast<Parallelogramm*>(colliderGroups.at(i).collisionBodies.at(j));
				if (q) {
					std::cout << "yeah3!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*q, *c);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}

					
				}

				PlaneCollider* w = dynamic_cast<PlaneCollider*>(colliderGroups.at(i).collisionBodies.at(j));
				if (w) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*w, *c);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}

					
				}

				Sphere* e = dynamic_cast<Sphere*>(colliderGroups.at(i).collisionBodies.at(j));
				if (e) {
					std::cout << "yeah!" << std::endl;
					std::vector<glm::vec3> points = getCollideP(*c, *e);
					for (auto m : points) {
						std::cout << "CollidePoint: " << m.x << "," << m.y << "," << m.z << std::endl;
					}

					
				}

			}

		}

	}
}