#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Skeleton.h"


class Bone : public Object{
public:

	Bone(Skeleton* skeleton, Object* parent = NULL, glm::vec3 pos = glm::vec3(0), glm::vec3 angle = glm::vec3(0));

	//Bone(Skeleton* skeleton,
	//	int BoneID // ID �����(��� �������� ����� ��� ������)
	//	,int parentBoneID // ID ������������ �����(��� �������� ����� = 0)
	//	, Mesh* mesh // ���, ����������� � �����
	//	, glm::vec3 position // ������� � ������������ ������ ������������ ������������ �����(��� �������� ����� - ������� ������ � ������������)
	//	, glm::vec3 angle
	//);
	glm::mat4 getTransformMatrix() override;
	~Bone() override {}

private:

	Skeleton* skeleton;	
	int boneID;

};