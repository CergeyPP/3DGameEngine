#pragma once
#include <glm/glm.hpp>

// Point is a glm::vec3 vector

struct Section {
	glm::vec3 p1, p2;
	Section(glm::vec3 P1 = glm::vec3(0), glm::vec3 P2 = glm::vec3(0)) : p1(P1), p2(P2) {}
};

struct Line {
	glm::vec3 p0, vec;
	Line(glm::vec3 P = glm::vec3(0), glm::vec3 Vec = glm::vec3(0)) :p0(P), vec(Vec) {}
};

struct Plane {
	float a, b, c, d;
	Plane(glm::vec3 p0, glm::vec3 p1, glm::vec3 p2) {
		glm::vec3 A = p1 - p0, B = p2 - p0;
		glm::vec3 n = glm::vec3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);

		n = glm::normalize(n);

		a = n.x;
		b = n.y;
		c = n.z;
		d = -(n.x * p0.x + n.y * p0.y + n.z * p0.z);
	}
	Plane(float A, float B, float C, float D) {
		a = A; b = B; c = C; d = D;
	}
};

Line sectionToLine(Section sec);
Line getPlaneCrossLine(Plane a, Plane b);
bool isCrossLines(Line a, Line b);
glm::vec3 getCrossLines(Line a, Line b);
bool isPointOnSection(Section sec, glm::vec3 p);
bool isPointOnLine(Line line, glm::vec3 p);
bool isPointOnPlane(Plane plane, glm::vec3 p);
bool isLineCrossPlane(Plane plane, Line line);
glm::vec3 getLineCrossPlane(Plane plane, Line line);
bool isPointInPolygon(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C);