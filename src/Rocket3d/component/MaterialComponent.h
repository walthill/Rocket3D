#ifndef MATERIAL_COMP_H
#define MATERIAL_COMP_H

//TODO: make this & mesh component trackable

#include "Component.h"

class RK_Shader;
class ShaderManager;

///Engine-based built-in shader identifiers
enum ShaderType { UNLIT_SHADER = -1, STANDARD_SHADER }; //unlit not functional as of 9/5/18

struct MaterialData
{
	RK_Shader* shader;
	ShaderType shaderType;

	MaterialData() : shader(nullptr), shaderType(STANDARD_SHADER) {};
	MaterialData(RK_Shader* s, ShaderType t) : shader(s), shaderType(t) {};
};

const MaterialData ZERO_MAT_DATA;

class MaterialComponent : public Component
{
	//Hold a pointer to a shader. On create, grab reference from the back end shader manager
	public:
		MaterialComponent(const ComponentId& id);
		~MaterialComponent() {};

		MaterialData getData() { return mMaterialData; };
		RK_Shader* getShader() { return mMaterialData.shader; };
		ShaderType getShaderKey() { return mMaterialData.shaderType; };

		void setData(const MaterialData& data) { mMaterialData = data; }
		void setShader(RK_Shader* shader) { mMaterialData.shader = shader; };
		void setShaderKey(const ShaderType& key) { mMaterialData.shaderType = key; };


	private:
		MaterialData mMaterialData;
};

#endif // !MATERIAL_COMP_H
