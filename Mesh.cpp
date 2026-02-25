#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLuint* indices, GLsizeiptr vertSize, GLsizeiptr indSize,ShaderType type)
    : VBO1(vertices, vertSize), EBO1(indices, indSize)
{
    VAO1.Bind();

    switch (type)
    {
        case ShaderType::BASIC:
            VBO1.Bind();
            EBO1.Bind();
            VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

			break;
		case ShaderType::DEFAULT:
            VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
            VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			break;
        case ShaderType::TEXTURE:
            VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
            VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            break;
    }
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    scale = 0.0f;
    indexCount = static_cast<GLsizei>(indSize / sizeof(GLuint));
	texture = nullptr;
}
void Mesh::Draw(Shader& shader)
{
    shader.Activate();
    VAO1.Bind();
    EBO1.Bind();


	switch (shader.type)
    {
        case ShaderType::BASIC:
            break;
        case ShaderType::DEFAULT:
        {
            GLuint uniID = glGetUniformLocation(shader.ID, "scale");
            glUniform1f(uniID, scale);
            break;
        }
        case ShaderType::TEXTURE:
        {
            GLuint uniID = glGetUniformLocation(shader.ID, "scale");
            glUniform1f(uniID, scale);
            texture->texUnit(shader, "tex0", 0);
            texture->Bind();
            break;
        }
        case ShaderType::TRANSFORM:
            break;
    }
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
void Mesh::Delete()
{
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
	if (texture != nullptr)
	    texture->Delete();
}