#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::load(GLuint num, const char *path) {
	if (ID != -1) {
		ERROR_FLT("Double loading of texture");
		return;
	}

	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + num);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		DEBUG_S(">>> Texture loaded " << "width:" << width << " height: " << height);
	}
	else {
		ERROR_FLT("Failed to load texture");
	}

	stbi_image_free(data);
}

void Texture::bind(GLuint num) {
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture() {
	if (ID != -1) {
		glDeleteTextures(1, &ID);
		DEBUG_S(">>> Texture delete");
	}
}