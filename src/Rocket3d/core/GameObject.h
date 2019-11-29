#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <RocketMath/Vector3.h>
#include "../component/Component.h"

class MaterialComponent;
class MeshComponent;
class TransformComponent;

class GameObject : public Trackable 
{
	public:
		GameObject();
		~GameObject();

		void destroy();

		void render();

		void setId(uint32 id) { mId = id; }
		void setTransformHandle(TransformComponent* comp) { mpTransform = comp; }
		void connectTransform(ComponentId transfromId) { mTransformId = transfromId; }
		void connectMesh(ComponentId meshId) { mMeshId = meshId; }
		void connectMaterial(ComponentId materialId) { mMaterialId = materialId; }

		uint32 getId() { return mId; }
		ComponentId getTransformId() { return mTransformId; };
		ComponentId getMeshId() { return mMeshId; };
		ComponentId getMaterialId() { return mMaterialId; };
	
		TransformComponent* getTransform() { return mpTransform; }
		MeshComponent* getMesh();
		MaterialComponent* getMaterial();

	private:
		uint32 mId; //change in GameObjectId
		ComponentId mMaterialId;
		ComponentId mMeshId;
		ComponentId mTransformId;

		TransformComponent* mpTransform;
};

#endif // !GAME_OBJ_H
