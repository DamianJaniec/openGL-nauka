#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID); //generowanie obiektu VAO
}
/*void VAO::linkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind(); //wiązanie bufora wierzcholkow (ustawienie jako aktywnego)
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //przypisanie bufora wierzcholkow do obiektu VAO
	glEnableVertexAttribArray(layout); //włączenie atrybutu wierzcholkow
}*/
void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO.Bind(); //wiązanie bufora wierzcholkow (ustawienie jako aktywnego)
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset); //przypisanie bufora wierzcholkow do obiektu VAO
	glEnableVertexAttribArray(layout); //włączenie atrybutu wierzcholkow
}
void VAO::Bind()
{
	glBindVertexArray(ID); //wiązanie obiektu VAO (ustawienie jako aktywnego)
}
void VAO::Unbind()
{
	glBindVertexArray(0); //odwiązanie obiektu VAO (ustawienie jako nieaktywnego)
}
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID); //usunięcie obiektu VAO
}
