#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	glGenBuffers(1, &ID); //generowanie bufora wierzcholkow
	glBindBuffer(GL_ARRAY_BUFFER, ID); //wiązanie bufora (ustawienie jako aktywnego)
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //przypisanie danych do bufora
	
}
void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID); //wiązanie bufora (ustawienie jako aktywnego)
}
void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); //odwiązanie bufora (ustawienie jako nieaktywnego)
}
void VBO::Delete()
{
	glDeleteBuffers(1, &ID); //usunięcie bufora
}