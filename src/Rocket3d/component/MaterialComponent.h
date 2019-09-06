#ifndef MATERIAL_COMP_H
#define MATERIAL_COMP_H

//TODO: make this & mesh component trackable

//#include "Component.h"
#include <RocketMath/Mat4.h>

class RK_Shader;
class ShaderManager;

enum ShaderType { UNLIT_SHADER = -1, STANDARD_SHADER }; //unlit not functional as of 9/5/18

class MaterialComponent /*: public Component */
{
	//Hold a pointer to a shader. On create, grab reference from the back end shader manager
	public:
		MaterialComponent(ShaderManager* man, ShaderType shaderType);
		~MaterialComponent() { mShader = nullptr; };

		void setMeshProperties(Mat4 modelMatrixValue);

		RK_Shader* getShader() { return mShader; };

	private:
		RK_Shader* mShader;
		ShaderType mShaderType;

};

#endif // !MATERIAL_COMP_H
