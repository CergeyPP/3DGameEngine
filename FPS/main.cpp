#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "LoadGLSL.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <math.h>
#include <string>
#include <ode/ode.h>

#include "Mesh.h"
#include "Bone.h"
#include "Skeleton.h"
#include "Texture.h"
#include "Object.h"
#include "Camera.h"
#include "Scene.h"
#include "CameraInputObject.h"
#include "Input.h"
#include "Light.h"
#include "DirectLight.h"
#include "PointLight.h"
#include "Model.h"
#include "Pawn.h"
#include "Player.h"
#include "PhysicTypes.h"
#include "Colliders.h"

Scene scene;

#pragma comment (lib,"DevIL.lib")
#pragma comment (lib,"ilut.lib")
#pragma comment (lib,"ilu.lib")

#define GLEW_STATIC

using namespace std;

float z = -3;
float x = 0;
float y = 1.62;

GLFWwindow* window;


int main() {

	ilInit();
	iluInit();

	if (glfwInit() == -1) {
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "FPS", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error to opening window";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true; // Флаг необходим в Core-режиме OpenGL. Инициализируем GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return -1;
	}

	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, keyCallBack);
	glfwSetCursorPosCallback(window, mouseCallBack);
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CW);

	Scene scene;
	Object::setScene(&scene);

	Mesh* mesh;

	Player pawn(glm::vec3(10, 0, 0), glm::vec3(0, 3.14, 0));
	Parallelogramm a(&pawn, 1, glm::vec3(0), glm::vec3(0.5));
	mesh = new Mesh(glm::vec3(-1), glm::vec3(0), &pawn);
	setCube(mesh, glm::vec3(0.5), glm::vec3(0.25, 0.25, 0.25));

	Camera camera1(window, glm::vec3(0.75, 0.75, 0), glm::vec3(0), pawn.getAttachObject(pawnAttachObjectHEAD));

	DirectLight dirLight(glm::vec3(1), glm::vec3(1, -1, 0));
	dirLight.material.diffuse = glm::vec3(1);
	dirLight.material.specular = glm::vec3(1);

	PointLight pointLight(glm::vec3(1, 1, 1), 1, glm::vec3(1, 5, -2), LightMaterial(glm::vec3(1), glm::vec3(1)), NULL);
	mesh = new Mesh(glm::vec3(0), glm::vec3(0), &pointLight);
	setCube(mesh, glm::vec3(0.1), glm::vec3(1, 1, 1));
	mesh->setRenderShaderType(SimplestShader);

	PointLight pointLight1(glm::vec3(1, 1, 1), 1, glm::vec3(1, 8, 1), LightMaterial(glm::vec3(1), glm::vec3(1)), NULL);
	mesh = new Mesh(glm::vec3(0), glm::vec3(0), &pointLight1);
	setCube(mesh, glm::vec3(0.1), glm::vec3(1, 1, 1));
	mesh->setRenderShaderType(SimplestShader);

	//B/OBJ format/blasterA.obj
	Model model("blasters/blasterB.obj", glm::vec3(5), glm::vec3(0, 0.5, -0.4), glm::vec3(0), pawn.getAttachObject(pawnAttachObjectLEFT_HAND));
	Model model1("blasters/blasterA.obj", glm::vec3(5), glm::vec3(0, 0.5, -0.4), glm::vec3(0), pawn.getAttachObject(pawnAttachObjectRIGHT_HAND));
	//Model Jotaro("Jotaro.obj", glm::vec3(0.045), glm::vec3(0, 0, 0), glm::vec3(glm::radians(0.f), glm::radians(90.f), 0));
	//Model ORA("scene.gltf", glm::vec3(0.135), glm::vec3(-2, 0, 0), glm::vec3(glm::radians(-90.f), glm::radians(90.f), 0));
	Object obj(glm::vec3(0, 0, 0));

	Parallelogramm b(&obj, 0, glm::vec3(0), glm::vec3(2, 1, 1));
	mesh = new Mesh(glm::vec3(-1, -0.5, -0.5), glm::vec3(0), &obj);
	setCube(mesh, glm::vec3(2, 1, 1), glm::vec3(1));

	GLuint tex;
	loadTexture(&tex, "cont.png");
	GLuint spec;
	loadTexture(&spec, "cont_spec.png");


	/*mesh = new Mesh(glm::vec3(-50, -100, -50), glm::vec3(0));
	setCube(mesh, glm::vec3(100), glm::vec3(1, 1, 1), tex);
	mesh->setRenderShaderType(MySkeletonShader);
	mesh->material.specular = spec;*/

	GLuint shaderProgram = LoadShaders("VertexDefault.txt", "FragmentDefault.txt");
	GLuint shaderCube = LoadShaders("VertexCube.txt", "FragmentCube.txt");
	GLuint shader = LoadShaders("Vertex.txt", "Fragment.txt");

	scene.shaderCollector.addShader(MySkeletonShader, shaderProgram);
	scene.shaderCollector.addShader(SimplestShader, shaderCube);

	float time = glfwGetTime();

	while (glfwWindowShouldClose(window) == 0) {

		float currentTime = glfwGetTime();

		float seconds = currentTime - time;

		glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scene.update(seconds);
		Input::resetMouseOffset();
		scene.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		time = currentTime;
	}

	glfwTerminate();

	return 0;
}