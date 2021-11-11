#include "ShaderCollector.h"

void ShaderCollector::addShader(ShaderType type, GLuint shader) {
	shaders[type] = shader;
}

bool ShaderCollector::isShaderExists(ShaderType type) {

	auto shader = shaders.find(type);

	if (shader == shaders.end()) {
		return 0;
	}
	else if (shaders[type] == 0)
			return 0;

	return 1;
}

GLuint ShaderCollector::getShader(ShaderType type) {
	return shaders[type];
}
