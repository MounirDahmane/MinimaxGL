#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>

class Shader
{
public:
	unsigned int ID;
	std::pair<const char*, const char*> Path;

	Shader(const char* VertexShaderSourcePath, const char* FragmentShaderSourcePath)
		:Path(VertexShaderSourcePath, FragmentShaderSourcePath)
	{
		std::ifstream VS_File;
		std::ifstream FS_File;

		std::string VS_code;
		std::string FS_code;

		std::string vsHolder;
		std::string fsHolder;

		std::stringstream vsStream, fsStream;

		// just ensure that the streams will throw exceptions

		VS_File.exceptions(std::ifstream::failbit | std::ifstream::badbit); // or another way to do this is remove failbit 
		FS_File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			VS_File.open(VertexShaderSourcePath);
			FS_File.open(FragmentShaderSourcePath);

			try
			{
				if (VS_File.is_open())
				{
					while (std::getline(VS_File, vsHolder))
					{
						VS_code += vsHolder + "\n";
					}
				}
			}
			catch (std::ifstream::failure e) {}

			//vsStream << VS_File.rdbuf();
			fsStream << FS_File.rdbuf();

			VS_File.close();
			FS_File.close();

			//vsHolder = vsStream.str();
			fsHolder = fsStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::FAILED::OPEN::SHADER_FILES\n" << std::endl;
		}

		const char* vShaderCode = VS_code.c_str();
		const char* fShaderCode = fsHolder.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		CheckError(vertex, 1);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		CheckError(fragment, 2);

		Shader::ID = glCreateProgram();
		glAttachShader(Shader::ID, vertex);
		glAttachShader(Shader::ID, fragment);
		glLinkProgram(Shader::ID);

		CheckError(Shader::ID, 3);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	~Shader()
	{
		glDeleteProgram(this->ID);
	}
	void use()
	{
		glUseProgram(Shader::ID);
	}
	void SetUniform1f(const char* uniform_name, float x)
	{
		glUniform1f(glGetUniformLocation(Shader::ID, uniform_name), x);
	}
	void SetUniform1i(const char* uniform_name, int Vx)
	{
		glUniform1i(glGetUniformLocation(Shader::ID, uniform_name), Vx);
	}
	void SetUniform3f(const char* uniform_name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(Shader::ID, uniform_name), x, y, z);
	}

private:

	void CheckError(unsigned int shader, int type)
	{
		// 1 : vs, 2 : fs, else ps
		int success;
		char InfoLog[512];

		if (type == 1)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, InfoLog);
				std::cout << "ERROR::VERTEX::SHADER::FAILED_COMPILATION\n" << InfoLog;
				std::cout << "THE_PATH : " << Shader::Path.first << "\n" << std::endl;
			}
		}
		else if (type == 2)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, InfoLog);
				std::cout << "ERROR::FRAGMENT::SHADER::FAILED_COMPILATION\n" << InfoLog;
				std::cout << "THE_PATH : " << Shader::Path.second << "\n" << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 512, NULL, InfoLog);
				std::cout << "ERROR::PROGRAM::SHADER::FAILED_LINKING\n" << InfoLog;
			}
		}
	}

};