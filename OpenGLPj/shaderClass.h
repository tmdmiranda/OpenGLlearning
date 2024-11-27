#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>




std::string get_file_contents(const char* filename);

class Shader
{
	public:
		GLuint ID;
		// CONSTRUCTOR THAT BULDS THE SHADER PROGRAM FROM 2 DIFFERENT SHADERS
		Shader(const char* vertexFile, const char* fragmentFile);
		
		void Activate();
		void Delete();
	private:
		// CHECKS IF DEIFFERENT SHADERS COMPILE AND LINK CORRECTLY
		void compileErrors(unsigned int shader, const char* type);
};


#endif