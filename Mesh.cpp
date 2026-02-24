#include "Mesh.h"

Mesh::Mesh(GLfloat* vertices, GLuint* indices, GLsizeiptr vertSize, GLsizeiptr indSize,short type)
    : VBO1(vertices, vertSize), EBO1(indices, indSize)
{
    if (type == 0)
    {
        VAO1.Bind();
        VBO1.Bind();
        EBO1.Bind();
        VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    }
    else if(type==1)
    {
        VAO1.Bind();
        
        VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
        VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    }
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();
    scale = 0.0f;
}
void Mesh::Draw(Shader& shader)
{
    shader.Activate();
    VAO1.Bind();
    EBO1.Bind();

    if (shader.type == 1)
    {
        GLuint uniID = glGetUniformLocation(shader.ID, "scale");
        glUniform1f(uniID, scale);
    }
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}
void Mesh::Delete()
{
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
}