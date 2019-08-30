/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of tutorials from Learn OpenGL
	(https://learnopengl.com)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 RK_Shader.h
	=========================
	This class encapsulates OpenGL vertex and fragment shaders. 
	Shaders are written in GLSL. 

********/

#ifndef RK_SHADER_H
#define RK_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../logging/RK_Log.h"
#include <RocketMath/MathUtils.h>

class RK_Shader 
{
	public:
		
		unsigned int shaderID; //program ID

		/***
			* Constructor that takes in vertex and fragment shader and calls init()
		***/
		RK_Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
		{
			mVertShaderPath = vertexPath;
			mFragShaderPath = fragmentPath;

			init();
		}

		/***
			* Initialize shader by reading GLSL code from file, compiling, and linking shaders  
		***/
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
				char vFilePath[500], fFilePath[500];

				strcpy_s(vFilePath, mSHADER_FILE_PATH);
				strcat_s(vFilePath, mVertShaderPath);

				strcpy_s(fFilePath, mSHADER_FILE_PATH);
				strcat_s(fFilePath, mFragShaderPath);

				vertShaderFile.open(vFilePath, std::ifstream::in);
				fragShaderFile.open(fFilePath, std::ifstream::in);

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
				RK_CORE_ERROR_ALL("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
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
				RK_CORE_ERROR_ALL("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
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
				RK_CORE_ERROR_ALL("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
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
				RK_CORE_ERROR_ALL("ERROR::SHADER::PROGRAM::LINKING_FAILED");
			}
			else 
			{ 
				std::cout << "LINKING >>>>>>> [SUCCESSFUL]" << std::endl << std::endl; 
			}

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		/***
			* Execute shader
		***/
		void use()
		{
			glUseProgram(shaderID);
		}

		/***
			* Set boolean uniform in the shader
		***/
		void setBool(const std::string &name, const bool &value) const
		{
			glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);
		}

		/***
			* Set int uniform in the shader
		***/
		void setInt(const std::string &name, const int &value) const
		{
			glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
		}

		/***
			* Set float uniform in the shader
		***/
		void setFloat(const std::string &name, const float &value) const
		{
			glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
		}

		/***
			* Set Matrix4 uniform in the shader
		***/
		void setMat4(const std::string &name, const Mat4 &mat)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 
													1, GL_TRUE, mat.getMatrixValues());
		}

		/***
			* Set Vector3 uniform in the shader
		***/
		void setVec3(const std::string &name, const Vector3 &value)
		{	
			glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, value.toArray());
		}

	private:
		//TODO: add ability to re-set bools, ints, floats - vectors that are reapplied on build?
		//reapply vars w/ reassignVariables()

		const char* mSHADER_FILE_PATH = "../RocketEngine/shader/glsl/";
		const char* mVertShaderPath;
		const char* mFragShaderPath;
};

#endif // !RK_SHADER_H
