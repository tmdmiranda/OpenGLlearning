#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include "Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

GLfloat vertices[] =
{
	//COORDINATES				//COLORS

   -0.5f,  -0.5f, 0.0f,			1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
   -0.5f,   0.5f, 0.0f,			0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	0.5f,	0.5f, 0.0f,			0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	0.5f,	-0.5f, 0.0f,	    1.0f, 1.0f, 1.0f,	1.0f, 0.0f
};

// Indices para ordem vertices
GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};


int main()
{
	//INITIALIZE GLFW
	glfwInit();
	//Tell GLFW what version of OPENGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//TELL GLFW WE ARE USING CORE PROFILE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//CREATE WINDOW
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Hello", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	// Gera Shader object usando as shaders default.vert e default.frag

	Shader shaderProgram("default.vert", "default.frag");

	// Gera um Vertex Array Object e liga-o
	VAO VAO1;
	VAO1.Bind();

	//Gera um Vertex Buffer Object e liga-o oas vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Gera um Element Buffer Object e liga-o aos indices
	EBO EBO1(indices, sizeof(indices));

	//Liga os atributos VBO como coordenadas e cores ao VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Da unbind para prevenir que seja modficado
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	//Obtem a referencia do uniform scale da shader
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture

	Texture betty("betty.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	betty.texUnit(shaderProgram, "tex0", 0);

	
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		// Dizer ao opengl que shaderProgram usar
		shaderProgram.Activate();
		// Ativar a textura para ser renderizada
		betty.Bind();
		// Da um valor ao uniform; NOTA: Tem de ser sempre feito apos ativar o shaderProgram
		glUniform1f(uniID, 0.5f); 

		// dar bind ao VAO para o OPENGL o usar
		VAO1.Bind();
		// desenhar o triangulo
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
	//Apaga os objetos
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	betty.Delete();
	shaderProgram.Delete();
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}