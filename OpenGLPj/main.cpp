#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();


	//Tell GLFW what version of OPENGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//TELL GLFW WE ARE USING CORE PROFILE
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};


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

	// Criar objeto vertex shader e obter a referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// encaixar o vertexShaderSource ao objeto vertexShader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compilar o vertexShader
	glCompileShader(vertexShader);


	//Mesma coisa que o anterior mas para o fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//Criar o shaderProgram e obter a sua referencia
	GLuint shaderProgram = glCreateProgram();

	//Encaixar as shaders no shaderprogram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//linkagem do programa
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	// Criar objetos container para Vertex Array Object e Vertex Buffer Object
	GLuint VAO, VBO;

	//Gerar o VAO E VBO com apenas 1 objeto cada
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Bind = selecionar o VAO como o atual Vertex Array Object
	glBindVertexArray(VAO);

	// Bind ao vbo, especificando como GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduzir os vertices no VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configurar o vertex attribute para o opengl saber como ler o VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// ligar o vertex attribute para o OPENGL saber para o usar
	glEnableVertexAttribArray(0);

	// dar bind ao VAO e VBO a 0 para nao acidentalmente o modificarmos
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);






	
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		// Dizer ao opengl que shaderProgram usar
		glUseProgram(shaderProgram);
		// dar bind ao VAO para o OPENGL o usar
		glBindVertexArray(VAO);
		// desenhar o triangulo
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}


	//Apagar todos os objetos que criamos
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}