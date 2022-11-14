#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		ShaderProgram = glCreateProgram();
		CompileShaderFromFile(vertexPath, GL_VERTEX_SHADER);
		CompileShaderFromFile(fragmentPath, GL_FRAGMENT_SHADER);
		glLinkProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_LINK_STATUS);
#ifndef __APPLE__
		glValidateProgram(ShaderProgram);
		CheckErrors(ShaderProgram, "PROGRAM", GL_VALIDATE_STATUS);
#endif // !__APPLE__
    }
	~Shader()
	{
		glDeleteProgram(ShaderProgram);
	}
	void UseProgram()
	{
		glUseProgram(ShaderProgram);
	}
	void SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z);
	}
private:
	GLuint ShaderProgram;
	void CompileShaderFromFile(const char* path, GLenum ShaderType)
	{
		std::string code;
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			shaderFile.open(path);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			shaderFile.close();
			code = shaderStream.str();
		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLU_READ: " << e.what() << std::endl;
		}
		const GLchar* shaderCode = code.c_str();
		GLuint shader = glCreateShader(ShaderType);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);
		CheckErrors(shader, "SHADER", GL_COMPILE_STATUS);
		glAttachShader(ShaderProgram, shader);
		glDeleteShader(shader);
    }
	void CheckErrors(GLuint obj, std::string type, GLenum checkStatus)
	{
		GLint success;
		if (type == "SHADER")
		{
			glGetShaderiv(obj, checkStatus, &success);
			if (!success)
			{
				GLchar infoLog[1024];
				glGetShaderInfoLog(obj, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
				exit(-1);
            }
		}
		else if (type == "PROGRAM")
		{
			glGetShaderiv(obj, checkStatus, &success);
			if (!success)
			{
				GLchar infoLog[1024];
				glGetShaderInfoLog(obj, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
				exit(-1);
			}
		}
	}
};