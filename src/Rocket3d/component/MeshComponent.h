/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		 MeshComponent.h
	=========================
	This file contains the definition for the Mesh Component object. 
	Inlucdes info for Mesh data and matrix uniforms

********/

#ifndef MESH_COMP_H
#define MESH_COMP_H

#include <RocketMath/MathUtils.h>
#include "Component.h"
#include "../../RocketEngine/shader/ShaderManager.h"

class Model;

const static std::string modelFileLocation = "../../assets/models/";

/***************************************************************************//**
 * @brief 	Data used in every mesh component.
 *
 * This struct contains data and constructors that will serve as foundational data
 * for every mesh
 ******************************************************************************/
struct MeshComponentData
{
	bool isLoaded;			///< Flag to set when model is loaded
	std::string modelName;  ///< Name of model to load
	std::string shaderKey;	///< Shader identifier

	Model* mesh;			///< Reference to the model
	RK_Shader* shader;		///< Reference to the mesh's shader

	///Default constructor sets all values to zero
	MeshComponentData() : isLoaded(false), mesh(nullptr), shader(nullptr), modelName(""), shaderKey("") {};

	///Constructor that takes in values for struct variables
	MeshComponentData(std::string name, std::string shaderKey, RK_Shader* s) :
		isLoaded(false), mesh(nullptr), shader(s), shaderKey(shaderKey), modelName(name) {};
};

const MeshComponentData ZERO_MESH_DATA;

/***************************************************************************//**
 * @brief 	The component for Meshes.
 *
 * This class, derived from Component, contains data and uniform names
 * needed to render 3d models.
 ******************************************************************************/
class MeshComponent : public Component
{
	public:

		/**********************************************************************//**
		* Creates component with the given id value.
		*
		* @param id ComponentId value assigned to this instance of the Component class
		*************************************************************************/
		MeshComponent(const ComponentId& id);

		///Default deconstructor
		~MeshComponent();

		///Load model from file
		void load();
		///Cleanup
		void cleanup();

		///Access the mesh component data
		MeshComponentData* getData() { return &mMeshData; }
		///Access the mesh shader reference
		RK_Shader* getShader() { return mMeshData.shader; }
		///Access the mesh model reference
		Model* getMesh();

		/**********************************************************************//**
		 * Set mesh data
		 *
		 * @param data MeshComponent struct with mesh data to store in the component
		 *************************************************************************/
		void setData(const MeshComponentData& data) { mMeshData = data; }

		/**********************************************************************//**
		 * Set shader refernce
		 *
		 * @param shader A reference to a RK_Shader to be assign to the component's mesh data
		 *************************************************************************/
		void setShader(RK_Shader* shader) { mMeshData.shader = shader; }
		
		/**********************************************************************//**
		 * Set model refernce
		 *
		 * @param mesh A reference to a Model to be assigned to the component's mesh data
		 *************************************************************************/
		void setMesh(Model* mesh) { mMeshData.mesh = mesh; }

		/**********************************************************************//**
		 * Set model visibility
		 *
		 * @param show A boolean to set the isEnabled flag to show or hide the model when rendering
		 *************************************************************************/
		void setMeshVisible(bool show);
		
		/**********************************************************************//**
		 * Set model visibility
		 *
		 * @param position			The world position of the model
		 * @param scale				The scale of the model
		 * @param rotationAxis		The rotational axis of the model
		 * @param rotationAngle		The rotation angle of the model
		 *************************************************************************/
		void process(Vector3 position = Vector3::zero, Vector3 scale = Vector3::one,
					 Vector3 rotatonAxis = Vector3::one, float rotationAngle = 0);
		
		/**********************************************************************//**
		 * Render model
		 *
		 * @param shaderMan A reference to the shader manager to set model matrix uniform
		 *************************************************************************/
		void render(ShaderManager* shaderMan);
		
	private: 
		const std::string MATRIX_NAME = "model";
		Mat4 modelMatrixValues = Mat4::identity;
		MeshComponentData mMeshData;
};

#endif // !MESH_COMP_H
