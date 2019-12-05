#include "RK_Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../logging/RK_Log.h"


RK_Shader::RK_Shader(const char* vertexPath, const char* fragmentPath)
{
	mVertShaderPath = vertexPath;
	mFragShaderPath = fragmentPath;
	init();
}

void RK_Shader::init()
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

void RK_Shader::use()
{
	glUseProgram(shaderID);
}

void RK_Shader::setBool(const std::string& name, const bool& value) const
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniform1i(location, (int)value);
}

void RK_Shader::setInt(const std::string& name, const int& value) const
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniform1i(location, value);
}

void RK_Shader::setFloat(const std::string& name, const float& value) const
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniform1f(location, value);
}

void RK_Shader::setMat4(const std::string& name, const Mat4& mat) const
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_TRUE, mat.getMatrixValues());
}

void RK_Shader::setVec3(const std::string& name, const Vector3& value)
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniform3fv(location, 1, value.toArray());
}

rk_uniformLocation RK_Shader::getUniformLocation(std::string name) const
{
	auto locationIndex = mUniformLocationCache.find(name);
	if (locationIndex != mUniformLocationCache.end())
		return mUniformLocationCache[name];

	rk_uniformLocation location = glGetUniformLocation(shaderID, name.c_str());
	mUniformLocationCache[name] = location;
	return location;
}