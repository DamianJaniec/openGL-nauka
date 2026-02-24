#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; //ID programu shaderowego
	short type;
	Shader(const char* vertexPath, const char* fragmentPath,short _type); //konstruktor, który tworzy program shaderowy na podstawie plików z kodem shadera

	void Activate(); //użycie programu shaderowego
	void Delete(); //usunięcie programu shaderowego

};

#endif