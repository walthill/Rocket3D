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

#include <unordered_map>
#include <RocketMath/MathUtils.h>

typedef int rk_uniformLocation;

class RK_Shader 
{
	public:
		
		unsigned int shaderID; //program ID

		/***
			* Constructor that takes in vertex and fragment shader and calls init()
		***/
		RK_Shader(std::string vertexPath, std::string fragmentPath);

		/***
			* Initialize shader by reading GLSL code from file, compiling, and linking shaders  
		***/
		void init();

		std::pair<std::string, std::string> loadFromFile();

		void compileShaders(const char* vertShaderCode, const char* fragShaderCode);

		/***
			* Execute shader
		***/
		void use();

		void destroyShader(int shaderObject);

		/***
			* Set boolean uniform in the shader
		***/
		void setBool(const std::string& name, const bool& value) const;

		/***
			* Set int uniform in the shader
		***/
		void setInt(const std::string& name, const int& value) const;

		/***
			* Set float uniform in the shader
		***/
		void setFloat(const std::string& name, const float& value) const;
	
		/***
			* Set Matrix4 uniform in the shader
		***/
		void setMat4(const std::string& name, const Mat4& mat) const;

		/***
			* Set Vector3 uniform in the shader
		***/
		void setVec3(const std::string& name, const Vector3& value);

		/***
			* Get uniform location, either from cache or an OpenGL call
		***/
		rk_uniformLocation getUniformLocation(std::string name) const;

	private:
		//TODO: add ability to re-set bools, ints, floats - vectors that are reapplied on build?
		//reapply vars w/ reassignVariables()
		std::string mSHADER_FILE_PATH = "../RocketEngine/shader/glsl/";
		std::string mVertShaderPath;
		std::string mFragShaderPath;

		mutable std::unordered_map<std::string, rk_uniformLocation> mUniformLocationCache;
};

#endif // !RK_SHADER_H
