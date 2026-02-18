#include "EBO.h"

EBO::EBO(GLuint* indicies, GLsizeiptr size)
{
	glGenBuffers(1, &ID); //generowanie bufora indeksow
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //wiązanie bufora (ustawienie jako aktywnego)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indicies, GL_STATIC_DRAW); //przypisanie danych do bufora
}
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID); //wiązanie bufora (ustawienie jako aktywnego)
}
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //odwiązanie bufora (ustawienie jako nieaktywnego)
}
void EBO::Delete()
{
	glDeleteBuffers(1, &ID); //usunięcie bufora
}