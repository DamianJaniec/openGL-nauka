#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "ShaderType.h"

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; //ID programu shaderowego

	ShaderType type;
	Shader(ShaderType _type);

	void Activate(); //użycie programu shaderowego
	void Delete(); //usunięcie programu shaderowego

};

#endif