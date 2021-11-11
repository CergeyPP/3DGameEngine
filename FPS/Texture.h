#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

bool loadTexture(GLuint* texture, std::string name);

GLuint generateTextureFromColor(glm::vec3 color);