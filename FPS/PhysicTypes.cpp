#include "PhysicTypes.h"
#include <iostream>
#define EPS 1e-20

bool isCrossLines(Line a, Line b) {

	int step = 1;

	if (a.vec == glm::vec3(0) || b.vec == glm::vec3(0)) return 0;
	step++;

	glm::vec3 p4 = b.p0 + b.vec;
	Plane plane(a.p0, a.p0 + a.vec, b.p0);
	if (plane.a * p4.x + plane.b * p4.y + plane.c * p4.z + plane.d != 0) {
		//std::cout << "Crossing lines: a.p0 = (" << a.p0.x << "," << a.p0.y << "," << a.p0.z << "), a.vec = (" << a.vec.x << "," << a.vec.y << "," << a.vec.z << "), ";
		//std::cout << "b.p0 = (" << b.p0.x << "," << b.p0.y << "," << b.p0.z << "), b.vec = (" << b.vec.x << "," << b.vec.y << "," << b.vec.z << ") - ";
		//std::cout << "Failed on step " << step << std::endl;
		return 0;
	}
	step++;
	if (b.vec.x * a.vec.y - a.vec.x * b.vec.y == 0 && b.vec.y * a.vec.z - a.vec.y * b.vec.z == 0 && b.vec.z * a.vec.x - a.vec.z * b.vec.x == 0) {
		return 0;
	}
	step++;

	return 1;
}

glm::vec3 getCrossLines(Line a, Line b) {

	if (b.vec.x * a.vec.y - a.vec.x * b.vec.y != 0) {
		float w = (a.vec.x * (b.p0.y - a.p0.y) - a.vec.y * (b.p0.x - a.p0.x)) / (b.vec.x * a.vec.y - a.vec.x * b.vec.y);
		return b.p0 + b.vec * w;
	}
	else if (b.vec.y * a.vec.z - a.vec.y * b.vec.z != 0) {

		float w = (a.vec.y * (b.p0.z - a.p0.z) - a.vec.z * (b.p0.y - a.p0.y)) / (b.vec.y * a.vec.z - a.vec.y * b.vec.z);
		return b.p0 + b.vec * w;
	}
	else if (b.vec.z * a.vec.x - a.vec.z * b.vec.x != 0) {

		float w = (a.vec.z * (b.p0.x - a.p0.x) - a.vec.x * (b.p0.z - a.p0.z)) / (b.vec.z * a.vec.x - a.vec.z * b.vec.x);
		return b.p0 + b.vec * w;
	}
	else return glm::vec3(0);
}

Line sectionToLine(Section s) {
	return Line(s.p1, glm::normalize(s.p2 - s.p1));
}

Line getPlaneCrossLine(Plane a, Plane b) {

	Line line;

	//std::cout << "Plane a: a=" << a.a << ", b=" << a.b << ", c=" << a.c << ", d=" << a.d << std::endl;
	//std::cout << "Plane b: a=" << b.a << ", b=" << b.b << ", c=" << b.c << ", d=" << b.d << std::endl;

	glm::vec3 nA = glm::vec3(a.a, a.b, a.c);
	glm::vec3 nB = glm::vec3(b.a, b.b, b.c);

	line.vec = glm::vec3(nA.y * nB.z - nA.z * nB.y, nA.z * nB.x - nA.x * nB.z, nA.x * nB.y - nA.y * nB.x);

	if (line.vec == glm::vec3(0)) {
		line.p0 = glm::vec3(0);
	}
	else {

		/*if (glm::vec3(nA.x, nA.y * 0, nA.z) != glm::vec3(0)) {
			Plane c = Plane(a);
			a = b,
			b = c;
		}

		line.p0.y = 0;
		std::cout << b.a * a.c - a.a * b.c << std::endl;
		if (b.a * a.c - a.a * b.c == 0) line.p0.z = 0;
			else line.p0.z = (a.a * b.d - b.a * a.d) / (b.a * a.c - a.a * b.c);
		std::cout << b.a << std::endl;
		line.p0.x = (-b.d - b.c * line.p0.z) / b.a;*/
		/*line.p0.x = 0;
		line.p0.z = (a.b * b.d - b.b - a.d) / (a.c * b.b - a.b * b.c);
		line.p0.y = (-b.d - b.c * line.p0.z) / b.b;*/

		int isXgot = 0, isYgot = 0, isZgot = 0;

		if (line.vec.x == 0) {
			if (a.b == 0 && a.c == 0) {
				line.p0.x = -a.d / a.a;
				isXgot = 1;
			}
			else {
				line.p0.x = -b.d / b.a;
				isXgot = 2;
			}
		}
		if (line.vec.y == 0) {
			if (a.a == 0 && a.c == 0) {
				line.p0.y = -a.d / a.b;
				isYgot = 1;
			}
			else {
				line.p0.y = -b.d / b.b;
				isYgot = 2;
			}
		}
		if (line.vec.z == 0) {
			if (a.a == 0 && a.b == 0) {
				line.p0.z = -a.d / a.c;
				isZgot = 1;
			}
			else {
				line.p0.z = -b.d / b.c;
				isZgot = 2;
			}
		}
		
		if (line.vec.x == 0) {
			if (line.vec.y == 0) line.p0.z = 0;
			else if (line.vec.z == 0) line.p0.y = 0;
			else {
				Plane m[2] = { a, b };
				isXgot -= 1;
				Plane needP = m[1 - isXgot];

				line.p0.z = 0;
				line.p0.y = -needP.d / -needP.b;
			}
		} else if (line.vec.y == 0) {
			if (line.vec.z == 0) line.p0.x = 0;
			else {
				Plane m[2] = { a, b };
				isYgot -= 1;
				Plane needP = m[1 - isYgot];

				line.p0.z = 0;
				line.p0.x = -needP.d / -needP.a;
			}
		}
		else if (line.vec.z == 0) {
			Plane m[2] = { a, b };
			isZgot -= 1;
			Plane needP = m[1 - isZgot];

			line.p0.y = 0;
			line.p0.x = -needP.d / -needP.a;
		}
		else {
			line.p0.z = 0;
			//std::cout << b.a * a.c - a.a * b.c << std::endl;
			line.p0.y = (a.a * b.d - b.a * a.d) / (b.a * a.b - a.a * b.b);
			//std::cout << b.a << std::endl;
			line.p0.x = (-b.d - b.c * line.p0.z) / b.a; 
				/*line.p0.x = 0;
				line.p0.z = (a.b * b.d - b.b - a.d) / (a.c * b.b - a.b * b.c);
				line.p0.y = (-b.d - b.c * line.p0.z) / b.b;*/
		}

	}

	return line;
}

bool isPointOnSection(Section sec, glm::vec3 p) {

	///*if (sec.p1.x > sec.p2.x) {
	//	glm::vec3 c = sec.p1;
	//	sec.p1 = sec.p2;
	//	sec.p2 = c;
	//}

	//if (sec.p1.x > p.x || sec.p2.x < p.x) return 0;
	//else if (sec.p1.x - sec.p2.x == 0)
	//{
	//	if (sec.p1.y > sec.p2.y) {
	//		glm::vec3 c = sec.p1;
	//		sec.p1 = sec.p2;
	//		sec.p2 = c;
	//	}
	//	if (sec.p1.y > p.y || sec.p2.y < p.y) return 0;
	//}
	//glm::vec3 vec1 = glm::vec3((p.x - sec.p1.x) * (p.x - sec.p1.x), (p.y - sec.p1.y) * (p.y - sec.p1.y), (p.z - sec.p1.z) * (p.z - sec.p1.z));
	//glm::vec3 vec2 = glm::vec3((sec.p2.x - sec.p1.x) * (sec.p2.x - sec.p1.x), (sec.p2.y - sec.p1.y) * (sec.p2.y - sec.p1.y), (sec.p2.z - sec.p1.z) * (sec.p2.z - sec.p1.z));

	//glm::vec3 W = glm::normalize(vec1 * vec1) - glm::normalize(vec2 * vec2);

	//

	//if (W == glm::vec3(0)) {
	//	std::cout << "Checking: vec1: " << vec1.x << ", " << vec1.y << ", " << vec1.z << ";\n";
	//	std::cout << "          vec2: " << vec2.x << ", " << vec2.y << ", " << vec2.z << ";\n";
	//	return 1;
	//}
	//return 0;*/

	//if ((p.x - sec.p1.x) * (sec.p2.y - sec.p1.y) == (p.y - sec.p1.y) * (sec.p2.x - sec.p1.x) && (p.y - sec.p1.y) * (sec.p2.z - sec.p1.z) == (p.z - sec.p1.z) * (sec.p2.y - sec.p1.y)) {
	//	if (sec.p1.x > sec.p2.x) {
	//		float c = sec.p1.x;
	//		sec.p1.x = sec.p2.x;
	//		sec.p2.x = c;
	//	}
	//	if (sec.p1.y > sec.p2.y) {
	//		float c = sec.p1.y;
	//		sec.p1.y = sec.p2.y;
	//		sec.p2.y = c;
	//	}
	//	if (sec.p1.z > sec.p2.z) {
	//		float c = sec.p1.z;
	//		sec.p1.z = sec.p2.z;
	//		sec.p2.z = c;
	//	}
	//	if (sec.p1.x <= p.x && sec.p2.x >= p.x &&
	//		sec.p1.z <= p.z && sec.p2.z >= p.z &&
	//		sec.p1.y <= p.y && sec.p2.y >= p.y) {

	//		//std::cout << "Crossed section: (" << sec.p1.x << ", " << sec.p1.y << ", " << sec.p1.z << "), ";
	//		//std::cout << "(" << sec.p2.x << ", " << sec.p2.y << ", " << sec.p2.z << "), Point: ";
	//		//std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;

	//		return 1;
	//	}
	//}
	//else return 0;

	if (!isPointOnLine(sectionToLine(sec), p)) return 0;

	if (sec.p1.x > sec.p2.x) {
		float c = sec.p1.x;
		sec.p1.x = sec.p2.x;
		sec.p2.x = c;
	}
	if (sec.p1.y > sec.p2.y) {
		float c = sec.p1.y;
		sec.p1.y = sec.p2.y;
		sec.p2.y = c;
	}
	if (sec.p1.z > sec.p2.z) {
		float c = sec.p1.z;
		sec.p1.z = sec.p2.z;
		sec.p2.z = c;
	}

	if (sec.p1.x <= p.x && sec.p2.x >= p.x &&
		sec.p1.z <= p.z && sec.p2.z >= p.z &&
		sec.p1.y <= p.y && sec.p2.y >= p.y) {

		//std::cout << "Crossed section: (" << sec.p1.x << ", " << sec.p1.y << ", " << sec.p1.z << "), ";
		//std::cout << "(" << sec.p2.x << ", " << sec.p2.y << ", " << sec.p2.z << "), Point: ";
		//std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;

		return 1;
	}

	return 0;

}

bool isPointOnLine(Line sec, glm::vec3 p) {

	glm::vec3 W = glm::normalize(Line(sec.p0, p - sec.p0).vec* Line(sec.p0, p - sec.p0).vec) - glm::normalize(sec.vec* sec.vec);

	if (W == glm::vec3(0)) return 1;
	return 0;
}

bool isPointOnPlane(Plane plane, glm::vec3 p) {
	return (plane.a * p.x + plane.b * p.y + plane.c * p.z + plane.d == 0);
}

bool isLineCrossPlane(Plane plane, Line line) {
	float scalar = plane.a * line.vec.x + plane.b * line.vec.y + plane.c * line.vec.z;
	if (scalar == 0 && !isPointOnPlane(plane, line.p0)) return 0;
	else return 1;
}

glm::vec3 getLineCrossPlane(Plane plane, Line line) {

	float t = -(plane.d + plane.a * line.p0.x + plane.b * line.p0.y + plane.c * line.p0.z);
	t /= (plane.a * line.vec.x + plane.b * line.vec.y + plane.c * line.vec.z);

	return line.p0 + line.vec * t;
}

bool isPointInPolygon(glm::vec3 P, glm::vec3 A, glm::vec3 B, glm::vec3 C) {

	Plane a(A, B, P), b(B, C, P), c(C, A, P);

	glm::vec3 n1 = glm::normalize(glm::vec3(a.a, a.b, a.c));
	glm::vec3 n2 = glm::normalize(glm::vec3(b.a, b.b, b.c));
	glm::vec3 n3 = glm::normalize(glm::vec3(c.a, c.b, c.c));

	float scalar1 = n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
	float scalar2 = n2.x * n3.x + n2.y * n3.y + n2.z * n3.z;

	return (scalar1 <= 1+EPS && scalar1 >= 1-EPS && scalar2 >= 1-EPS && scalar2 <= 1+EPS);
}

bool isSectionOnPlane(Plane plane, Section sec) {
	return ((sec.p1.x * plane.a + sec.p1.y * plane.b + sec.p1.z * plane.c + plane.d == 0) &&
		(sec.p2.x * plane.a + sec.p2.y * plane.b + sec.p2.z * plane.c + plane.d == 0));
}