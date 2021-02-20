/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 ShaderManager.h
	=========================
	This class managers all engine shaders

********/

#ifndef R3_SHADER_MAN_H
#define R3_SHADER_MAN_H

#include <rkm/Vector3.h>
#include <rkm/Mat4.h>
#include "../util/EngineUtils.h"
#include <map>
#include "RK_Shader.h"

const ShaderKey STANDARD_SHADER_KEY = "standardLightingShader";
const ShaderKey EMITTER_SHADER_KEY = "emitter";

class ShaderManager : public rkutil::Trackable
{
	public:
		/***
			* Constrcutor
		***/
		ShaderManager();
		/***
			* Deconstrcutor cleans shader vector
		***/
		~ShaderManager();

		/***
			* Destroys shaders in shader vector
		***/
		void clean();

		/***
			* NOT IN USE - Used for live building of shaders
		***/
		static void buildShaders();

		/***
			* Run shader program by passing in the corresponding key
		***/
		void useShaderByKey(const ShaderKey& key);

		/***
			* Add shader to the vector along with an identifier
		***/
		void addShader(ShaderKey id, RK_Shader* shader) { mShaderList[id] = shader; };
		
		/***************************************
			Assign value to the shader currently in use
		****************************************/

		void setShaderInt(const std::string& intName, int value);
		void setShaderBool(const std::string& boolName, bool value);
		void setShaderFloat(const std::string& floatName, float value);
		void setShaderMat4(const std::string& matrixName, const rkm::Mat4 &mat);
		void setShaderVec3(const std::string& vecName, float x, float y, float z); //Use three float values
		void setShaderVec3(const std::string& vecName, const rkm::Vector3 &vec); //use Vector object in param

		/***
			* Access currently used shader
		***/
		RK_Shader* getShaderInUse() { return getShaderByKey(mShaderInUse); };
		/***
			* Access shader by its ShaderKey identifier
		***/
		RK_Shader* getShaderByKey(const ShaderKey& key);

		/***
			* Access the entire list of shaders
		***/
		std::map<ShaderKey, RK_Shader*> getShaderList() { return mShaderList; };
		
	private:
		static std::map<ShaderKey, RK_Shader*> mShaderList;
		RK_Shader* mpCurrentShader;
		ShaderKey mShaderInUse;

};

#endif // !R3_SHADER_MANAGER
