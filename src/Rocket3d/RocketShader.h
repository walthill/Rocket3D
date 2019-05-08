#ifndef ROCKET_SHADER_H
#define ROCKET_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class RocketShader 
{
	public:
		
		unsigned int shaderID; //program ID

		RocketShader(const GLchar* vertexPath, const GLchar* fragmentPath)
		{
			mVertShaderPath = vertexPath;
			mFragShaderPath = fragmentPath;

			init();
		}

		void init()
		{
			std::string vertexCode;
			std::string fragmentCode;

			std::ifstream vertShaderFile;
			std::ifstream fragShaderFile;

			vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
			fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try
			{
				//Constructor only needs file name and not path
				char vFilePath[100], fFilePath[100];

				strcpy_s(vFilePath, mSHADER_FILE_PATH);
				strcat_s(vFilePath, mVertShaderPath);

				strcpy_s(fFilePath, mSHADER_FILE_PATH);
				strcat_s(fFilePath, mFragShaderPath);

				vertShaderFile.open(vFilePath);
				fragShaderFile.open(fFilePath);

				std::stringstream vShaderStream, fShaderStream;

				//Read files into streams
				vShaderStream << vertShaderFile.rdbuf();
				fShaderStream << fragShaderFile.rdbuf();

				vertShaderFile.close();
				fragShaderFile.close();

				//Convert stream into string
				vertexCode = vShaderStream.str();
				fragmentCode = fShaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}

			const char* vertShaderCode = vertexCode.c_str();
			const char* fragShaderCode = fragmentCode.c_str();

			// Compile shaders
			// ---------------------------------------------------------------
			std::cout << std::endl << "=======\tSHADER -- BUILD STARTED =======" << std::endl << std::endl;

			unsigned int vertexShader, fragmentShader; //Shader obj

			//Debug vars
			int success;
			char infoLog[512];

			//VERTEX SHADER
			std::cout << "(" << mVertShaderPath << ") -- VERTEX SHADER COMPILATION" << std::endl;
			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertShaderCode, NULL);
			glCompileShader(vertexShader);

			//Check if compilation successful
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			else { std::cout << "COMPILATION >>>>>>> [SUCCESSFUL]" << std::endl; }

			//FRAGMENT SHADER
			std::cout << "(" << mFragShaderPath << ") -- FRAGMENT SHADER COMPILATION" << std::endl;
			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragShaderCode, NULL);
			glCompileShader(fragmentShader);

			//Check if compilation successful
			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			else { std::cout << "COMPILATION >>>>>>> [SUCCESSFUL]" << std::endl; }


			//SHADER PROGRAM
			std::cout << "PERFORMING SHADER LINK" << std::endl;
			shaderID = glCreateProgram();
			glAttachShader(shaderID, vertexShader);
			glAttachShader(shaderID, fragmentShader);
			glLinkProgram(shaderID);

			// Check if linking successful
			glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}
			else { std::cout << "LINKING >>>>>>> [SUCCESSFUL]" << std::endl << std::endl; }
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void use()
		{
			glUseProgram(shaderID);
		}

		void setBool(const std::string &name, bool value) const
		{
			glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
		}

		void setInt(const std::string &name, int value) const
		{
			glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
		}

		void setFloat(const std::string &name, float value) const
		{
			glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
		}

	private:
		//TODO: add ability to re-set bools, ints, floats - vectors that are reapplied on build?
		//reapply vars w/ reassignVariables()
		const char* mSHADER_FILE_PATH = "shaders/";
		const char* mVertShaderPath;
		const char* mFragShaderPath;
};

#endif // !ROCKET_SHADER_H
