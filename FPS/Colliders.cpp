#include "Colliders.h"
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <memory>

Parallelogramm::Parallelogramm(Object* basicObject, float mass, glm::vec3 Offset, glm::vec3 Sides) : Collider(basicObject, mass, 0) {
	sides = Sides;
	offset = Offset - Sides / 2.f;

	float max = sides.x + fabsf(offset.x);
	if (sides.y + fabsf(offset.y) > max) max = sides.y + fabsf(offset.y);
	if (sides.z + fabsf(offset.z) > max) max = sides.z + fabsf(offset.z);

	collisionDetectionRadius = max * sqrtf(2);
}

std::vector<glm::vec3> Parallelogramm::getNormales() {

	std::vector<glm::vec3> vec = {
		glm::vec3(0,-1,0),
		glm::vec3(-1,0,0),
		glm::vec3(0,0,-1),
		glm::vec3(1,0,0),
		glm::vec3(0,0,1),
		glm::vec3(0,1,0)
	};

	return vec;
}

std::vector<Section> Parallelogramm::getSections() {

	glm::vec3 c = offset;
	offset += getPosition();

	std::vector<Section> lines;
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));

	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z)));
	/*lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	lines.push_back(Section(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));
	lines.push_back(Section(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));

	lines.push_back(Section(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z)));*/

	offset = c;

	return lines;
}

std::vector<Plane> Parallelogramm::getPlanes() {

	glm::vec3 c = offset;
	offset += getPosition();

	std::vector<Plane> planes;
	planes.push_back(Plane(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x, offset.y, offset.z + sides.z)));
	planes.push_back(Plane(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x, offset.y, offset.z + sides.z)));
	planes.push_back(Plane(glm::vec3(offset.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z)));

	planes.push_back(Plane(glm::vec3(offset.x + sides.x, offset.y, offset.z), glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z)));
	planes.push_back(Plane(glm::vec3(offset.x + sides.x, offset.y, offset.z + sides.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z), glm::vec3(offset.x, offset.y, offset.z + sides.z)));
	planes.push_back(Plane(glm::vec3(offset.x, offset.y + sides.y, offset.z), glm::vec3(offset.x + sides.x, offset.y + sides.y, offset.z), glm::vec3(offset.x, offset.y + sides.y, offset.z + sides.z)));

	offset = c;

	return planes;
}

std::vector<glm::vec3> getCollideP(PlaneCollider a, PlaneCollider b) {

	Line line = getPlaneCrossLine(a, b);

	std::vector<glm::vec3> vec;
	vec.push_back(line.p0);
	vec.push_back(line.p0 + line.vec);

	return vec;
}

std::vector<glm::vec3> getCollideP(PlaneCollider a, Sphere o) {

	// check geometry note
	return std::vector <glm::vec3>();
}

std::vector<glm::vec3> getCollideP(PlaneCollider a, Parallelogramm d) {
	
	std::vector<glm::vec3> crossPoints;

	glm::mat4 transform = d.getBasicObject()->getTransformMatrix();
	glm::vec3 objectOffset = glm::vec3(transform * glm::vec4(0, 0, 0, 1));
	d.offset += objectOffset;

	std::vector<Section> lines = d.getSections();

	std::vector<Plane> planes;
	planes.push_back(Plane(glm::vec3(d.offset.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x + d.sides.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x, d.offset.y, d.offset.z + d.sides.z)));
	planes.push_back(Plane(glm::vec3(d.offset.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x, d.offset.y + d.sides.y, d.offset.z), glm::vec3(d.offset.x, d.offset.y, d.offset.z + d.sides.z)));
	planes.push_back(Plane(glm::vec3(d.offset.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x + d.sides.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x, d.offset.y + d.sides.y, d.offset.z)));

	planes.push_back(Plane(glm::vec3(d.offset.x + d.sides.x, d.offset.y, d.offset.z), glm::vec3(d.offset.x + d.sides.x, d.offset.y, d.offset.z + d.sides.z), glm::vec3(d.offset.x + d.sides.x, d.offset.y + d.sides.y, d.offset.z)));
	planes.push_back(Plane(glm::vec3(d.offset.x + d.sides.x, d.offset.y, d.offset.z + d.sides.y), glm::vec3(d.offset.x, d.offset.y+d.sides.y, d.offset.z + d.sides.z), glm::vec3(d.offset.x, d.offset.y, d.offset.z + d.sides.z)));
	planes.push_back(Plane(glm::vec3(d.offset.x, d.offset.y + d.sides.y, d.offset.z), glm::vec3(d.offset.x + d.sides.x, d.offset.y + d.sides.y, d.offset.z), glm::vec3(d.offset.x, d.offset.y + d.sides.y, d.offset.z + d.sides.z)));
	
	

	for (int i = 0; i < planes.size(); i++) {

		Line crossLine = getPlaneCrossLine(a, planes[i]);
		if (crossLine.vec == glm::vec3(0)) continue;

		for (int j = 0; j < lines.size(); j++) {
			if (isCrossLines(crossLine, sectionToLine(lines[j]))) {
				glm::vec3 point = getCrossLines(crossLine, sectionToLine(lines[i]));

				if (isPointOnSection(lines[i], point)) crossPoints.push_back(point);
			}
		}
	}

	return crossPoints;
}

std::vector<glm::vec3> getCollideP(Parallelogramm a, Parallelogramm b) {
	std::vector<glm::vec3> crossPoints;
	   
	std::vector<Section> linesA = a.getSections();

	std::vector<Plane> planesA = a.getPlanes();

	std::vector<Section> linesB = b.getSections();

	std::vector<Plane> planesB = b.getPlanes();

	int lineIndexFromPlane[6][4] = {
		0, 2, 7, 9,
		1, 2, 8, 10,
		0, 1, 11, 6,
		4, 5, 6, 7,
		9, 8, 5, 3,
		10, 11, 4, 3
	};


	for (int i = 0; i < planesA.size(); i++) {

		for (int k = 0; k < planesB.size(); k++) {
			Line crossLine = getPlaneCrossLine(planesA[i], planesB[k]);
			if (crossLine.vec == glm::vec3(0)) {
				continue;
			}	

			std::vector<glm::vec3> pointsA;

			for (int j = 0; j < 4; j++) {

				if (isCrossLines(crossLine, sectionToLine(linesA[lineIndexFromPlane[i][j]]))) {

					glm::vec3 point = getCrossLines(crossLine, sectionToLine(linesA[lineIndexFromPlane[i][j]]));
					if (isPointOnSection(linesA[lineIndexFromPlane[i][j]], point)) {
						pointsA.push_back(point);
						//break;

					}
					
				}

			}

			std::vector<glm::vec3> pointsB;

			for (int j = 0; j < 4; j++) {

				if (isCrossLines(crossLine, sectionToLine(linesB[lineIndexFromPlane[k][j]]))) {

					glm::vec3 point = getCrossLines(crossLine, sectionToLine(linesB[lineIndexFromPlane[k][j]]));
					if (isPointOnSection(linesB[lineIndexFromPlane[k][j]], point)) {
						pointsB.push_back(point);
						//break;

					}

				}

			}

			if (pointsA.size() >= 2) {
				Section secsegment(pointsA[0], pointsA[1]);

				for (auto a : pointsB) {
					if (isPointOnSection(secsegment, a))
						crossPoints.push_back(a);
				}
			}
			if (pointsB.size() >= 2) {
				Section secsegment(pointsB[0], pointsB[1]);

				for (auto a : pointsA) {
					if (isPointOnSection(secsegment, a))
						crossPoints.push_back(a);
				}
			}

			//crossPoints.insert(crossPoints.end(), pointsA.begin(), pointsA.end());
			//crossPoints.insert(crossPoints.end(), pointsB.begin(), pointsB.end());
		}
	}

	/*std::sort(crossPoints.begin(), crossPoints.end());
	crossPoints.erase(unique(crossPoints.begin(), crossPoints.end()), crossPoints.end());*/
	
	return crossPoints;
}

std::vector<glm::vec3> getCollideP(Parallelogramm a, Sphere o) {

	// check geometry note
	return std::vector <glm::vec3>();
}

std::vector<glm::vec3> getCollideP(Sphere a, Sphere o) {

	// check geometry note
	return std::vector <glm::vec3>();
}