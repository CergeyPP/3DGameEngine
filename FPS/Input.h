#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const int WIDTH = 1600, HEIGHT = 900;

class Input {
public:

	static bool keyPressed[1024];
	static float mouseOffsetX;
	static float mouseOffsetY;

	//Input();

	static void resetMouseOffset();
};

//static Input* input = new Input();

void keyCallBack(GLFWwindow* window, int key, int scan, int action, int mode);

void mouseCallBack(GLFWwindow* window, double xpos, double ypos);