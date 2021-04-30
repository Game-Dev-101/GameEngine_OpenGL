#ifndef TEXTURE_2D_CLASS_H
#define TEXTURE_2D_CLASS_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture2D
{
	private :
		GLenum type;

	public:
		GLuint ID;
		Texture2D(const char* filename, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void TextureUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif
