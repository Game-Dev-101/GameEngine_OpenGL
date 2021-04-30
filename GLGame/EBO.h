#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class EBO
{
public:
	GLuint ID;

	/// <summary>
	/// Create EBO (Automatically Generate & Bind On Create)
	/// </summary>
	/// <param name="indices">Connector by uint array</param>
	/// <param name="size">Size of array memory</param>
	EBO(GLuint* indices, GLsizei size);

	void Bind();
	void UnBind();
	void Delete();
};

#endif
