#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct AnimationBoneTransform {
	glm::vec3 transform = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);

	AnimationBoneTransform(glm::vec3 trans = glm::vec3(0), glm::vec3 rot = glm::vec3(0)) {
		transform = trans;
		rotation = rot;
	}

	void setRot(glm::vec3 rot) {
		rotation = glm::vec3((3.141 / 180) * rot.x, (3.141 / 180) * rot.y, (3.141 / 180) * rot.z);
	}
};

struct AnimationPoseBones {
	float time = 1; // ������ ����(��� ������������ ������� �������������)
	std::vector<AnimationBoneTransform> bone; //bone[i] - ������� ���� i-�� �����(�� ���� �������� ������������� = T-pose ������� * ������� ����) 
};

struct Animation {
	std::vector<AnimationPoseBones> pose; // pose[i] - i-�� ���� � ������� ��������
};