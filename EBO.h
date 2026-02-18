#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	GLuint ID; //ID bufora indeksow
	EBO(GLuint* indicies, GLsizeiptr size); //konstruktor, który tworzy bufor indeksow na podstawie danych
	void Bind(); //wiązanie bufora (ustawienie jako aktywnego)
	void Unbind(); //odwiązanie bufora (ustawienie jako nieaktywnego)
	void Delete(); //usunięcie bufora
};

#endif 

#pragma once
