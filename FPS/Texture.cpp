#include "Texture.h"
#include <IL\il.h>
#include <IL\ilu.h>

bool loadTexture(GLuint* texture, std::string name) {

	glGenTextures(1, texture);

	GLubyte* imageData;
	ilLoad(IL_TYPE_UNKNOWN, name.c_str());
	// ���������, ��� �� ������ ��� �������� �����
	int err = ilGetError();
	if (err != IL_NO_ERROR)
	{
		const char* strError = iluErrorString(err);
		std::cout << strError << "\n";
		return -1;
	}
	// �������� ������ ��������
	int width = ilGetInteger(IL_IMAGE_WIDTH);          // ������
	int height = ilGetInteger(IL_IMAGE_HEIGHT);        // ������
	int size = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);      // ���� �� ������
	// ��������� ������ � ���� ��������
	imageData = ilGetData();
	ilEnable(IL_CONV_PAL);
	// ��� ������ �����������
	unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);

	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
	
}

GLuint generateTextureFromColor(glm::vec3 color) {

	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, &color[0]);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}