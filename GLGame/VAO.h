#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "VBO.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VAO
{
public:
	GLuint ID;
	VAO();

	void LinkAttribute(VBO vbo, GLuint layout, GLuint componentCount, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif