#include "Input.h" 


//Input::Input(){
//	for (int i = 0; i < 1024; i++)
//		keyPressed[i] = 0;
//}

bool Input::keyPressed[1024] = { 0 };
float Input::mouseOffsetX = 0;
float Input::mouseOffsetY = 0;

void Input::resetMouseOffset() {
	mouseOffsetX = 0;
	mouseOffsetY = 0;
}


void keyCallBack(GLFWwindow* window, int key, int scan, int action, int mode) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (action == GLFW_PRESS) {
		Input::keyPressed[key] = true;
	}

	if (action == GLFW_RELEASE) {
		Input::keyPressed[key] = false;
	}
}

void mouseCallBack(GLFWwindow* window, double xpos, double ypos) {

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	Input::mouseOffsetX = x - WIDTH / 2;
	Input::mouseOffsetY = y - HEIGHT / 2;

	glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
}