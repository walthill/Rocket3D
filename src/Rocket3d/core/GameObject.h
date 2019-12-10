#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <RocketMath/Vector3.h>
#include "../component/Component.h"

class MaterialComponent;
class MeshComponent;
class DirectionalLightComponent;
class PointLightComponent;
class SpotLightComponent;
class TransformComponent;

class GameObject : public Trackable 
{
	public:
		GameObject();
		~GameObject();

		void destroy();

		void update(float elapsedTime);
		void render();

		void setId(uint32 id) { mId = id; }
		void setTransformHandle(TransformComponent* comp) { mpTransform = comp; }
		void connectTransform(ComponentId transfromId) { mTransformId = transfromId; }
		void connectMesh(ComponentId meshId) { mMeshId = meshId; }
		void connectMaterial(ComponentId materialId) { mMaterialId = materialId; }
		void connectDirectionalLight(ComponentId lightId) { mDirectionalLightId = lightId; }
		void connectSpotLight(ComponentId lightId) { mSpotLightId = lightId; }
		void connectPointLight(ComponentId lightId) { mPointLightId = lightId; }


		uint32 getId() { return mId; }
		ComponentId getTransformId() { return mTransformId; };
		ComponentId getMeshId() { return mMeshId; };
		ComponentId getMaterialId() { return mMaterialId; };
		ComponentId getSpotLightId() { return mSpotLightId; }
		ComponentId getDirectionalLightId() { return mDirectionalLightId; }
		ComponentId getPointLightId() { return mPointLightId; }

		TransformComponent* getTransform() { return mpTransform; }
		MeshComponent* getMesh();
		MaterialComponent* getMaterial();
		SpotLightComponent* getSpotLight();
		DirectionalLightComponent* getDirectionalLight();
		PointLightComponent* getPointLight();

	private:
		uint32 mId; //change in GameObjectId
		ComponentId mMaterialId;
		ComponentId mMeshId;
		ComponentId mTransformId;

		ComponentId mPointLightId;
		ComponentId mDirectionalLightId;
		ComponentId mSpotLightId;

		TransformComponent* mpTransform;
};

#endif // !GAME_OBJ_H
