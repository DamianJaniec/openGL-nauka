#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
	GLuint ID; //ID obiektu VAO
	VAO(); //konstruktor, który tworzy obiekt VAO
	//void linkVBO(VBO& VBO, GLuint layout); //przypisanie bufora wierzcholkow do obiektu VAO
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset); //przypisanie atrybutu do obiektu VAO
	void Bind(); //wiązanie obiektu VAO (ustawienie jako aktywnego)
	void Unbind(); //odwiązanie obiektu VAO (ustawienie jako nieaktywnego)
	void Delete(); //usunięcie obiektu VAO
};

#endif 

