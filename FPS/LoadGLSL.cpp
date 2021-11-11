#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "LoadGLSL.h"
#include <iostream>

GLuint LoadShaders(const char* VertexPath, const char* FragmentPath) {

	std::fstream vertexFile;
	vertexFile.open(VertexPath);
	std::stringstream vertexData;

	vertexData << vertexFile.rdbuf();
	std::string vertexCode = vertexData.str();
	const GLchar* vVertexCode = vertexCode.c_str();

	//std::cout << vertexCode.c_str() << "\n";

	GLuint vertex;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vVertexCode, nullptr);
	glCompileShader(vertex);

	GLchar infoLog[512];
	GLint success;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR IN VERTEX SHADER COMPILATION\n" << infoLog << std::endl;
	}

	std::fstream fragmentFile;
	fragmentFile.open(FragmentPath);
	std::stringstream fragmentData;

	fragmentData << fragmentFile.rdbuf();
	std::string fragmentCode = fragmentData.str();
	const GLchar* vFragmentCode = fragmentCode.c_str();

	//std::cout << fragmentCode.c_str() << "\n";

	GLuint fragment;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &vFragmentCode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR IN FRAGMENT SHADER COMPILATION\n" << infoLog << std::endl;
	}

	fprintf(stdout, "Creating shader programm and bindeng shaders \n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertex);
	glAttachShader(ProgramID, fragment);
	glLinkProgram(ProgramID);

	int infoLogLength = 0;

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &success);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return ProgramID;
}