#include "shaderClass.h"

std::string get_file_contents(const char* filename)
{
		std::ifstream in(filename, std::ios::in | std::ios::binary);
		if (in)
		{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// Criar objeto vertex shader e obter a referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// encaixar o vertexShaderSource ao objeto vertexShader

	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compilar o vertexShader
	glCompileShader(vertexShader);


	//Mesma coisa que o anterior mas para o fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	 
	//Criar o shaderProgram e obter a sua referencia
	ID = glCreateProgram();

	//Encaixar as shaders no shaderprogram
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//linkagem do programa
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}