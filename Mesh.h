#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderProgram.h"
#include "Texture.h"

class Mesh
{

	VAO VAO1;
	VBO VBO1;
	EBO EBO1;

	GLsizei indexCount;

	//GLuint scaleID;
	GLfloat scale;

	Texture *texture;

public:
	Mesh(GLfloat* vertices, GLuint* indices, GLsizeiptr vertSize, GLsizeiptr indSize,ShaderType type);
	void Draw(Shader& shader);
	void Delete();
	void setScale(GLfloat _scale) { scale = _scale; }
	void setTexture(Texture* _texture) { texture = _texture; }
};

#endif
