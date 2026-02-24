#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	GLuint ID;
public:
	VAO();
	//void linkVBO(VBO& VBO, GLuint layout);
	void linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
	GLuint getID() { return ID; }
};

#endif // !VAO_CLASS_H

