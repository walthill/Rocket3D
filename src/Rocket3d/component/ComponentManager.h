#ifndef COMPONENT_MAN_H
#define COMPONENT_MAN_H

#include <map>
#include <vector>
#include <DeanLib/Trackable.h>
#include <DeanLib/MemoryPool.h>
//#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "LightComponent.h"

class ShaderManager;

class ComponentManager : public Trackable
{
	public:
		ComponentManager(uint32 maxSize, ShaderManager* shaderMan, ShaderKey lightingShaderKey);
		~ComponentManager();

		void clean();

		//TRANSFORM
		TransformComponent* getTransformComponent(const ComponentId& id);
		ComponentId allocateTransformComponent(const TransformData& data = ZERO_TRANSFORM_DATA);
		void deallocateTransformComponent(const ComponentId& id);

		//MESH
		MeshComponent* getMeshComponent(const ComponentId& id);
		ComponentId allocateMeshComponent(const ComponentId& meshId, const	MeshComponentData& data = ZERO_MESH_DATA);
		void deallocateMeshComponent(const ComponentId& id);

		//DIRECTIONAL LIGHT
		DirectionalLightComponent* getDirectionalLightComponent(const ComponentId& id);
		ComponentId allocateDirectionalLightComponent(const ComponentId& dirLightId, const DirectionalLightData& data = ZERO_DIRECTIONAL_LIGHT_DATA);
		void deallocateDirectionalLightComponent(const ComponentId& id);


		//POINT LIGHT
		PointLightComponent* getPointLightComponent(const ComponentId& id);
		ComponentId allocatePointLightComponent(const ComponentId& pointLightId, const PointLightData& data = ZERO_POINT_LIGHT_DATA);
		void deallocatePointLightComponent(const ComponentId& id);

		//SPOT LIGHT
		SpotLightComponent* getSpotlightComponent(const ComponentId& id);
		ComponentId allocateSpotlightComponent(const ComponentId& spotlightId, const	SpotLightData& data = ZERO_SPOTLIGHT_DATA);
		void deallocateSpotlightComponent(const ComponentId& id);

		void update(float elapsedTime);
		void processLightingComponents();
		void renderMeshes();

		int getNumberOfMeshes() { return mMeshComponentMap.size(); }
		int getNumberOfTransforms() { return mTransformComponentMap.size(); }
		int getNumberOfPointLights() { return mPointLightComponentMap.size(); }
		int getNumberOfSpotlights() { return mSpotlightComponentMap.size(); }
		int getNumberOfDirectionalLights() { return mDirectionalLightComponentMap.size(); }


	private:
		const std::string pointLightNumVar = "numPointLights";
		ShaderManager* mpShaderManagerHandle;
		ShaderKey mLightingShaderKey;

		MemoryPool mTransformPool;
		MemoryPool mMeshPool;
		MemoryPool mDirectionalLightPool;
		MemoryPool mPointLightPool;
		MemoryPool mSpotlightPool;

		std::map<ComponentId, TransformComponent*> mTransformComponentMap;
		std::map<ComponentId, MeshComponent*> mMeshComponentMap;
		std::map<ComponentId, PointLightComponent*> mPointLightComponentMap;
		std::map<ComponentId, DirectionalLightComponent*> mDirectionalLightComponentMap;
		std::map<ComponentId, SpotLightComponent*> mSpotlightComponentMap;

		static ComponentId msNextTransformComponentId;
		static ComponentId msNextMeshComponentId;
		static ComponentId msNextMaterialComponentId;
		static ComponentId msNextPointLightComponentId;
		static ComponentId msNextDirectionalLightComponentId;
		static ComponentId msNextSpotlightComponentId;
};

#endif // !COMPONENT_MAN_H
