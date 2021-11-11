#pragma once
#include "LoadGLSL.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <vector>
#include <string>

enum ShaderType {
	SimplestShader, 
	ModelShader,
	MySkeletonShader,
};

class ShaderCollector {
public:

	bool isShaderExists(ShaderType type);
	GLuint getShader(ShaderType type);
	void addShader(ShaderType type, GLuint shader);

private:

	std::map<ShaderType, GLuint> shaders;
	
	friend class Scene;
};