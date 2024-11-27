#include "VAO.h"


//CONSTRUCTOR GENERATES A VAO ID
VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

// Links a VBO TO THE VAO USING A CERTAIN LAYOUT
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	// ligar o vertex attribute para o OPENGL saber para o usar
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}