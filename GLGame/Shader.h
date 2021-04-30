#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cerrno>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string getFileContents(const char* filename);

class Shader
{
private:
	void compileError(unsigned int shader, const char* type);

public:
	/// <summary>
	/// Shader program ID
	/// </summary>
	GLuint ID;

	/// <summary>
	/// Reads and builds the shader into program
	/// </summary>
	/// <param name="vertexPath">Vertex Shader file path</param>
	/// <param name="fragmentPath">Fragment Shader file path</param>
	Shader(const char* vertexPath, const char* fragmentPath);

	/// <summary>
	/// Activate shader data
	/// </summary>
	void activateShader();

	/// <summary>
	/// Delete shader program from application
	/// </summary>
	void deleteProgram();

	/// <summary>
	/// Set variable boolean type value in shader script
	/// </summary>
	/// <param name="varName">Existing variable name in Shader Script</param>
	/// <param name="value">Type boolean set value</param>
	void setBool(const std::string& varName, bool value);

	/// <summary>
	/// Set variable integer type value in shader script
	/// </summary>
	/// <param name="varName">Existing variable name in Shader Script</param>
	/// <param name="value">Type integer set value</param>
	void setInt(const std::string& varName, int value);

	/// <summary>
	/// Set variable float type value in shader script
	/// </summary>
	/// <param name="varName">Existing variable name in Shader Script</param>
	/// <param name="value">Type float set value</param>
	void setFloat(const std::string& varName, float value);
};

#endif