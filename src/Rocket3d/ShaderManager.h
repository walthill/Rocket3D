#ifndef R3_SHADER_MAN_H
#define R3_SHADER_MAN_H

#include <vector>

class RocketShader;

class ShaderManager
{
	public:
		ShaderManager() { mShaderList = {}; };
		~ShaderManager();

		static void buildShaders();
		void useShaders();

		void addShader(RocketShader* shader) { mShaderList.push_back(shader); };

		std::vector<RocketShader*> getShaderList() { return mShaderList; };
		
	private:
		//TODO: make this a map with shader string-based ID's
		static std::vector<RocketShader*> mShaderList;

};

#endif // !R3_SHADER_MANAGER
