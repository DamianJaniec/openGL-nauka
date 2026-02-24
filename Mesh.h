#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderProgram.h"

class Mesh
{
public:
	VAO VAO1;
	VBO VBO1;
	EBO EBO1;

	//GLuint scaleID;
	GLfloat scale;

	Mesh(GLfloat* vertices, GLuint* indices, GLsizeiptr vertSize, GLsizeiptr indSize,short type);
	void Draw(Shader& shader);
	void Delete();
	void setScale(GLfloat _scale) { scale = _scale; }
};

#endif
