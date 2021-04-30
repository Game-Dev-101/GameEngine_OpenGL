#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VBO
{
public:
	GLuint ID;

	/// <summary>
	/// Create VBO (Automatically Generate & Bind On Create)
	/// </summary>
	/// <param name="vertices">Vertex Points by float array</param>
	/// <param name="size">Size of array memory</param>
	VBO(GLfloat* vertices, GLsizei size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
