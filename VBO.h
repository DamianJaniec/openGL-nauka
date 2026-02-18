#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
public:
	GLuint ID; //ID bufora wierzcholkow
	VBO(GLfloat* vertices, GLsizeiptr size); //konstruktor, który tworzy bufor wierzcholkow na podstawie danych
	void Bind(); //wiązanie bufora (ustawienie jako aktywnego)
	void Unbind(); //odwiązanie bufora (ustawienie jako nieaktywnego)
	void Delete(); //usunięcie bufora
};

#endif // !VBO_CLASS_H

