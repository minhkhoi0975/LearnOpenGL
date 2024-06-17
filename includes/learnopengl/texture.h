#pragma once

#include <memory>
#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
public:
	~Texture()
	{
		if (id != 0)
			Finalize();
	}

	void Init(const char* filePath, bool hasAlphaChannel = false)
	{
		// Generate a texture.
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		// Set the default wrapping mode.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set the default filtering mode.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load image.
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath, &width, &height, &channelCount, 0);
		if (!data)
		{
			stbi_image_free(data);
			return;
		}

		isImageValid = true;

		// Apply image to texture.
		glTexImage2D(GL_TEXTURE_2D, 0, hasAlphaChannel ? GL_RGBA : GL_RGB, width, height, 0, hasAlphaChannel ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	void Finalize()
	{
		glDeleteTextures(1, &id);
	}

	unsigned int GetId()
	{
		return id;
	}

	void Use()
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

private:
	unsigned int id = 0;
	int width = 0, height = 0, channelCount = 0;
	bool isImageValid = false;
};