#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{	
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = get_file_contents(vertexPath);
	std::string fragmentCode = get_file_contents(fragmentPath);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //utworzenie shadera wierzcholkowego
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //przypisanie kodu shadera
	glCompileShader(vertexShader); //kompilacja shadera
	compileErrors(vertexShader, "VERTEX"); //sprawdzenie błędów kompilacji shadera wierzcholkowego

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //utworzenie shadera fragmentowego
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); //przypisanie kodu shadera
	glCompileShader(fragmentShader); //kompilacja shadera
	compileErrors(vertexShader, "FRAGMENT"); //sprawdzenie błędów kompilacji shadera wierzcholkowego

	ID = glCreateProgram(); //utworzenie programu shaderowego
	glAttachShader(ID, vertexShader); //przypisanie shadera wierzcholkowego do programu
	glAttachShader(ID, fragmentShader); //przypisanie shadera fragmentowego do programu
	glLinkProgram(ID); //linkowanie programu shaderowego
	compileErrors(ID, "PROGRAM"); //sprawdzenie błędów linkowania programu shaderowego

	glDeleteShader(vertexShader); //usuwanie shadera wierzcholkowego (nie jest juz potrzebny)
	glDeleteShader(fragmentShader); //usuwanie shadera fragmentowego (nie jest juz potrzebny)

}
void Shader::Activate()
{
	glUseProgram(ID); //użycie programu shaderowego
}
void Shader::Delete()
{
	glDeleteProgram(ID); //usunięcie programu shaderowego
}
void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if(hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if(hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}