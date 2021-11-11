#include "Pawn.h"
#include "Bone.h"
#include "Mesh.h"



void Pawn::update(float second) {
	for (int i = 0; i < 4; i++) {
		skeletonParts[i].update(second);
	}
}

Object* Pawn::getAttachObject(pawnAttachObjectType type) {
	return attachObjects[type];
}

Pawn::Pawn(glm::vec3 pos, glm::vec3 angle, Object* parent)
	: Actor(pos, angle, parent){

	for (int i = 0; i < 4; i++) {
		skeletonParts[i].animStatys = 0;
	}

	//skeletonParts[pawnSkeletonLEGS].animStatys = 0;

	// pawnSkeletonBODY configuring
		{
			Skeleton* s = &skeletonParts[pawnSkeletonBODY];

			Mesh *mesh;

			s->bones.push_back(new Bone(s, NULL, glm::vec3(0, 4, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, 0, -1.0001), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 0.5, 2.0002), /*color*/glm::vec3(0, 0.25, 0));

			s->bones.push_back(new Bone(s, s->bones[0], glm::vec3(0, 0.5, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, 0, -1), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 3, 2), /*color*/glm::vec3(0.2, 0.2, 0.2));

			Animation anim;
			//	
			AnimationPoseBones bones;
			// animation 0(stand pose)
				// pose
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, -15, 0));
			bones.bone[1].setRot(glm::vec3(0, 15, 0));

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();

			// animation 1 (running)
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
			// animation 2 (default)
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
		}
	// pawnSkeletonLEGS configuring
		{
			Skeleton* body = &skeletonParts[pawnSkeletonBODY];
			Skeleton* s = &skeletonParts[pawnSkeletonLEGS];

			Mesh* mesh;

			s->bones.push_back(new Bone(s, body->bones[0], glm::vec3(0, 0, -0.5), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.505, -2, -0.505), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1.01, 2, 1.01), /*color*/glm::vec3(0, 0.25, 0));

			s->bones.push_back(new Bone(s, body->bones[0], glm::vec3(0, 0, 0.5), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.505, -2, -0.505), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1.01, 2, 1.01), /*color*/glm::vec3(0, 0.25, 0));

			s->bones.push_back(new Bone(s, s->bones[0], glm::vec3(0, -2, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(1, 0.75f, 0.46f));
			mesh->material.setSpecularColor(glm::vec3(0.2f, 0.2f, 0.2f));
			mesh->material.shininess = 2.f;

			s->bones.push_back(new Bone(s, s->bones[1], glm::vec3(0, -2, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(1, 0.75f, 0.46f));
			mesh->material.setSpecularColor(glm::vec3(0.2f, 0.2f, 0.2f));
			mesh->material.shininess = 2.f;

			Animation anim;
			//	
			AnimationPoseBones bones;
			// animation 0(stand pose)
				// pose
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(15, 30, 30));
			bones.bone[1].setRot(glm::vec3(-15, -30, 20));
			bones.bone[2].setRot(glm::vec3(0, 0, -30));
			bones.bone[3].setRot(glm::vec3(0, 0, -30));

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
			// animation 1
				// pose 1
			bones.time = 2;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);
			// pose 2
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, 45));
			bones.bone[1].setRot(glm::vec3(0, 0, -45));
			bones.bone[2].setRot(glm::vec3(0, 0, -45));
			bones.bone[3].setRot(glm::vec3(0, 0, -45));

			anim.pose.push_back(bones);
			// pose 3
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, 23));
			bones.bone[1].setRot(glm::vec3(0, 0, -30));
			bones.bone[2].setRot(glm::vec3(0, 0, -23));
			bones.bone[3].setRot(glm::vec3(0, 0, -60));

			anim.pose.push_back(bones);
			// pose 4
			bones.time = 2;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);
			// pose 5
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, -45));
			bones.bone[1].setRot(glm::vec3(0, 0, 45));
			bones.bone[2].setRot(glm::vec3(0, 0, -45));
			bones.bone[3].setRot(glm::vec3(0, 0, -45));

			anim.pose.push_back(bones);
			// pose 6
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, -30));
			bones.bone[1].setRot(glm::vec3(0, 0, 23));
			bones.bone[2].setRot(glm::vec3(0, 0, -60));
			bones.bone[3].setRot(glm::vec3(0, 0, -23));

			anim.pose.push_back(bones);


			s->animPatterns.push_back(anim);
			anim.pose.clear();

			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
		}
	// pawnSkeletonARMS configuring
		// left
		{
			Skeleton* body = &skeletonParts[pawnSkeletonBODY];
			Skeleton* s = &skeletonParts[pawnSkeletonARM_LEFT];

			Mesh* mesh;

			s->bones.push_back(new Bone(s, body->bones[1], glm::vec3(0, 2.5, -1.5), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5005, -2 + 0.5, -0.5005), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1.001, 2, 1.001), /*color*/glm::vec3(0.2, 0.2, 0.2));

			s->bones.push_back(new Bone(s, s->bones[0], glm::vec3(0, -1.5, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(1, 0.75f, 0.46f));
			mesh->material.setSpecularColor(glm::vec3(0.2f, 0.2f, 0.2f));
			mesh->material.shininess = 2.f;

			s->bones.push_back(new Bone(s, s->bones[1], glm::vec3(0, -2, 0), glm::vec3(0, glm::radians(-90.f), glm::radians(-90.f))));
			attachObjects[pawnAttachObjectLEFT_HAND] = s->bones.back();

			Animation anim;

			AnimationPoseBones bones;
			// animation 0(default)
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, 70));
			bones.bone[1].setRot(glm::vec3(0, 0, 20));
			//bones.bone[1].setRot(glm::vec3(0, 0, 90));

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
			// animation 1
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);
			s->animPatterns.push_back(anim);
			anim.pose.clear();

			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
		}
		// right
		{
			Skeleton* body = &skeletonParts[pawnSkeletonBODY];
			Skeleton* s = &skeletonParts[pawnSkeletonARM_RIGHT];

			Mesh* mesh;

			s->bones.push_back(new Bone(s, body->bones[1], glm::vec3(0, 2.5, 1.5), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5005, -2 + 0.5, -0.5005), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1.001, 2, 1.001), /*color*/glm::vec3(0.2, 0.2, 0.2));

			s->bones.push_back(new Bone(s, s->bones[0], glm::vec3(0, -1.5, 0), /*angle*/glm::vec3(0)));
			mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), s->bones.back());
			setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(1, 0.75f, 0.46f));
			mesh->material.setSpecularColor(glm::vec3(0.2f, 0.2f, 0.2f));
			mesh->material.shininess = 2.f;

			s->bones.push_back(new Bone(s, s->bones[1], glm::vec3(0, -2, 0), glm::vec3(0, glm::radians(-90.f), glm::radians(-90.f))));
			attachObjects[pawnAttachObjectRIGHT_HAND] = s->bones.back();

			Animation anim;

			AnimationPoseBones bones;
			// animation 0(default)
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			bones.bone[0].setRot(glm::vec3(0, 0, 70));
			bones.bone[1].setRot(glm::vec3(0, 0, 20));
			//bones.bone[1].setRot(glm::vec3(0, 0, 90));

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
			// animation 1
			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);
			s->animPatterns.push_back(anim);
			anim.pose.clear();

			bones.time = 1;
			bones.bone.assign(s->bones.size(), AnimationBoneTransform());

			anim.pose.push_back(bones);

			s->animPatterns.push_back(anim);
			anim.pose.clear();
		}

	//HEADobject configuring
		{
			GLuint Tex;
			if (loadTexture(&Tex, "cont.png") != 0) {
				std::cout << "Couldn't open file" << std::endl;
				Tex = 0;
			}

			Mesh* mesh;

			headNode.setBasicObject(skeletonParts[pawnSkeletonBODY].bones[1]);

			headNode.translate(glm::vec3(0, 3, 0));

			mesh = new Mesh(/*offest*/glm::vec3(-0.75, 0, -0.75), glm::vec3(0), &headNode);
			setCube(mesh, /*sides*/glm::vec3(1.5, 1.5, 1.5), /*color*/glm::vec3(1, 1, 1), Tex);
			GLuint spec;
			if (loadTexture(&spec, "cont_spec.png") != 0) {
				std::cout << "Couldn't open file" << std::endl;
				spec = 0;
			}
			else mesh->material.specular = spec;

			attachObjects[pawnAttachObjectHEAD] = &headNode;
		}


	skeletonParts[pawnSkeletonBODY].setBasicObject(this);
	skeletonParts[pawnSkeletonARM_RIGHT].setBasicObject(&skeletonParts[pawnSkeletonBODY]);
	skeletonParts[pawnSkeletonARM_LEFT].setBasicObject(&skeletonParts[pawnSkeletonBODY]);
	skeletonParts[pawnSkeletonLEGS].setBasicObject(&skeletonParts[pawnSkeletonBODY]);
}