#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLuint* indices, GLsizeiptr vertSize, GLsizeiptr indSize)
    : VBO1(vertices, vertSize), EBO1(indices, indSize)
{
    VAO1.Bind();
    VBO1.Bind();
    EBO1.Bind();
    VAO1.linkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
}