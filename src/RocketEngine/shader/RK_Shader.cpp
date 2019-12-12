#include "RK_Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include "../logging/RK_Log.h"


RK_Shader::RK_Shader(std::string vertexPath, std::string fragmentPath)
{
	mVertShaderPath = vertexPath;
	mFragShaderPath = fragmentPath;
	init();
}

void RK_Shader::init()
{
	std::pair<std::string, std::string> vertAndFragCode = loadFromFile();

	const char* vertexShaderCode = vertAndFragCode.first.c_str();
	const char* fragmentShaderCode = vertAndFragCode.second.c_str();

	compileShaders(vertexShaderCode, fragmentShaderCode);
}

std::pair<std::string, std::string> RK_Shader::loadFromFile()
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
		std::string vFilePath, fFilePath;

		vFilePath = mSHADER_FILE_PATH + mVertShaderPath;
		fFilePath = mSHADER_FILE_PATH + mFragShaderPath;

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

	return std::pair<std::string, std::string>(vertexCode, fragmentCode);
}

void RK_Shader::compileShaders(const char* vertShaderCode, const char* fragShaderCode)
{
	// Compile shaders
	// ---------------------------------------------------------------
	RK_CORE_LOG_ALL("=======\tSHADER -- BUILD STARTED =======");

	unsigned int vertexShader, fragmentShader; //Shader obj

	//Debug vars
	int success;
	char infoLog[512];

	//VERTEX SHADER
	RK_CORE_LOG_ALL("(" + mVertShaderPath + ") -- VERTEX SHADER COMPILATION");
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
	else { RK_CORE_INFO_ALL("COMPILATION >>>>>>> [SUCCESSFUL]"); }

	//FRAGMENT SHADER
	RK_CORE_LOG_ALL("(" + mFragShaderPath + ") -- FRAGMENT SHADER COMPILATION");
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
	else { RK_CORE_INFO_ALL("COMPILATION >>>>>>> [SUCCESSFUL]"); }

	//SHADER PROGRAM
	RK_CORE_LOG_ALL("PERFORMING SHADER LINK");
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
		RK_CORE_INFO_ALL("LINKING >>>>>>> [SUCCESSFUL]");
	}

	//Clean up
	destroyShader(vertexShader);
	destroyShader(fragmentShader);
}

void RK_Shader::use()
{
	glUseProgram(shaderID);
}

void RK_Shader::destroyShader(int shaderObject)
{
	glDeleteShader(shaderObject);	
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

void RK_Shader::setMat4(const std::string& name, const rkm::Mat4& mat) const
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniformMatrix4fv(location, MODIFY_SINGLE_OBJECT, GL_TRUE, mat.getMatrixValues());
}

void RK_Shader::setVec3(const std::string& name, const rkm::Vector3& value)
{
	rk_uniformLocation location = getUniformLocation(name);
	glUniform3fv(location, MODIFY_SINGLE_OBJECT, value.toArray());
}

rk_uniformLocation RK_Shader::getUniformLocation(std::string name) const
{
	//Find existing uniform, return its location value
	auto locationIndex = mUniformLocationCache.find(name);
	if (locationIndex != mUniformLocationCache.end())
		return locationIndex->second;

	//Get location from OpenGL, store in cache, and return
	rk_uniformLocation location = glGetUniformLocation(shaderID, name.c_str());
	mUniformLocationCache[name] = location;
	return location;
}