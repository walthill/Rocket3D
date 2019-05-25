#ifndef R3_SHADER_MAN_H
#define R3_SHADER_MAN_H

#include <RocketMath/Vector3.h>
#include "../util/EngineUtils.h"
#include <map>

class RK_Shader;

class ShaderManager
{
	public:
		ShaderManager() { mShaderList = {}; };
		~ShaderManager();

		void clean();

		static void buildShaders();

		//Run all stored shader programs
		void useShaders();
		
		void useShaderByKey(ShaderKey key);

		void addShader(ShaderKey id, RK_Shader* shader) { mShaderList[id] = shader; };
		
		/***************************************
			Assign value to the shader currently in use
		****************************************/

		void setShaderInt(std::string intName, int value);
		void setShaderBool(std::string boolName, bool value);
		void setShaderFloat(std::string floatName, float value);
		void setShaderMat4(std::string matrixName, const float *mat);
		void setShaderVec3(std::string vecName, float x, float y, float z); //Use three float values
		void setShaderVec3(std::string vecName, const Vector3& vec); //use Vector object in param

		RK_Shader* getShaderInUse() { return getShaderByKey(mShaderInUse); };
		RK_Shader* getShaderByKey(ShaderKey key);
		std::map<ShaderKey, RK_Shader*> getShaderList() { return mShaderList; };
		
	private:
		//TODO: make this a map with shader string-based ID's
		static std::map<ShaderKey, RK_Shader*> mShaderList;
		ShaderKey mShaderInUse;

};

#endif // !R3_SHADER_MANAGER
