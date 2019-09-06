#ifndef MESH_COMP_H
#define MESH_COMP_H

//#include "Component.h"
#include <RocketMath/MathUtils.h>

class MaterialComponent;
class RK_Shader;
class Model;

const static std::string modelFileLocation = "../../assets/models/";

class MeshComponent /*: public Component*/
{
	public:
		MeshComponent(std::string modelName); //takes in the model file location, and shader type
		~MeshComponent();

		void cleanup();

		void linkMaterialComponent(MaterialComponent* matComp) { mMaterialComponent = matComp; };

		void render(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one,
					Vector3 rotatonAxis = Vector3::one, float rotationAngle = 0);

	private: 
		Mat4 modelMatrixValues = Mat4::identity;

		Model* mMesh;
		MaterialComponent* mMaterialComponent;
};

#endif // !MESH_COMP_H
