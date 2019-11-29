#ifndef MESH_COMP_H
#define MESH_COMP_H

#include <RocketMath/MathUtils.h>
#include "Component.h"

class MaterialComponent;
class RK_Shader;
class Model;

const static std::string modelFileLocation = "../../assets/models/";

struct MeshComponentData
{
	bool isLoaded;
	std::string modelName;
	Model* mesh;
	RK_Shader* shader;

	MeshComponentData() : isLoaded(false), mesh(nullptr), shader(nullptr), modelName("") {};
	MeshComponentData(std::string name, RK_Shader* s) : isLoaded(false), mesh(nullptr), shader(s), modelName(name) {};
};

const MeshComponentData ZERO_MESH_DATA;

class MeshComponent : public Component
{
	public:
		MeshComponent(const ComponentId& id); //takes in the model file location, and shader type
		~MeshComponent();

		void load();
		void cleanup();

		MeshComponentData* getData() { return &mMeshData; }
		RK_Shader* getShader() { return mMeshData.shader; }
		Model* getMesh() { return mMeshData.mesh; }

		void setData(const MeshComponentData& data) { mMeshData = data; }
		void setShader(RK_Shader* shader) { mMeshData.shader = shader; }
		void setMesh(Model* mesh) { mMeshData.mesh = mesh; }

		void render(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one,
					Vector3 rotatonAxis = Vector3::one, float rotationAngle = 0);

	private: 
		const std::string MATRIX_NAME = "model";
		Mat4 modelMatrixValues = Mat4::identity;
		MeshComponentData mMeshData;
};

#endif // !MESH_COMP_H
