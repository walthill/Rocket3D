#ifndef R3_SHADER_MAN_H
#define R3_SHADER_MAN_H

#include "../util/EngineUtils.h"
//#include <RocketMath/MathUtils.h>
#include <map>
//#include "RocketShader.h"

class RocketShader;

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

		void addShader(ShaderKey id, RocketShader* shader) { mShaderList[id] = shader; };
		
		/***************************************
			Assign value to the shader currently in use
		****************************************/

		void setShaderInt(std::string intName, int value);
		void setShaderBool(std::string boolName, bool value);
		void setShaderFloat(std::string floatName, float value);
		void setShaderMat4(std::string matrixName, const float *mat);
		void setShaderVec3(std::string vecName, float x, float y, float z); //Use three float values
		void setShaderVec3(std::string vecName, const float *vec); //Overload to use Vector object in param

		RocketShader* getShaderByKey(ShaderKey key);
		std::map<ShaderKey, RocketShader*> getShaderList() { return mShaderList; };
		
	private:
		//TODO: make this a map with shader string-based ID's
		static std::map<ShaderKey, RocketShader*> mShaderList;
		ShaderKey mShaderInUse;

};

#endif // !R3_SHADER_MANAGER
