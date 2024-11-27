#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices para ordem vertices
GLuint indices[] =
{
	0,1,2,
	0,2,3,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4
};

const unsigned int width = 800;
const unsigned int height = 800;


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
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Hello", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create a window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

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

	
	//Texture

	Texture betty("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	betty.texUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	//Camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
	
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Dizer ao opengl que shaderProgram usar
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		betty.Bind();
		// dar bind ao VAO para o OPENGL o usar
		VAO1.Bind();
		// desenhar o triangulo
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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