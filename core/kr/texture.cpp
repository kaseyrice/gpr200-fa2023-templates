//texture.cpp
#include "texture.h"
#include "../ew/external/stb_image.h"
#include "../ew/external/glad.h"

unsigned int loadTexture(const char* filePath)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, numComponents;
	unsigned char* data = stbi_load(filePath, &width, &height, &numComponents, 0);
	if (data == NULL)
	{
		printf("Failed to load image %s", filePath);
		stbi_image_free(data);
		return 0;
	}

	//loadTexture...
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLenum format;

	//Determine the format of the image based on number of components.
	if (numComponents == 1)
	{
		format = GL_RED;
	}
	else if (numComponents == 2)
	{
		format = GL_RG;
	}
	else if (numComponents == 3)
	{
		format = GL_RGB;
	}
	else if (numComponents == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		format = NULL;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return texture;
}