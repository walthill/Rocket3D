#ifndef COMPONENT_MAN_H
#define COMPONENT_MAN_H

#include <map>
#include <vector>
#include <future>
#include <DeanLib/Trackable.h>
#include <DeanLib/MemoryPool.h>
#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

class ComponentManager : public Trackable
{
	public:
		ComponentManager(uint32 maxSize);
		~ComponentManager();

		void clean();

		TransformComponent* getTransformComponent(const ComponentId& id);
		ComponentId allocateTransformComponent(const TransformData& data = ZERO_TRANSFORM_DATA);
		void deallocateTransformComponent(const ComponentId& id);

		MeshComponent* getMeshComponent(const ComponentId& id);
		ComponentId allocateMeshComponent(const ComponentId& meshId, const	MeshComponentData& data = ZERO_MESH_DATA);
		void deallocateMeshComponent(const ComponentId& id);

		MaterialComponent* getMaterialComponent(const ComponentId& id);
		ComponentId allocateMaterialComponent(const ComponentId& materialId, const MaterialData& data = ZERO_MAT_DATA);
		void deallocateMaterialComponent(const ComponentId& id);

		void update(float elapsedTime);

		int getNumberOfMeshes() { return mMeshComponentMap.size(); }
		int getNumberOfMaterials() { return mMaterialComponentMap.size(); }
		int getNumberOfTransforms() { return mTransformComponentMap.size(); }

	private:
		MemoryPool mTransformPool;
		MemoryPool mMeshPool;
		MemoryPool mMaterialPool;

		std::map<ComponentId, TransformComponent*> mTransformComponentMap;
		std::map<ComponentId, MeshComponent*> mMeshComponentMap;
		std::map<ComponentId, MaterialComponent*> mMaterialComponentMap;

		static ComponentId msNextTransformComponentId;
		static ComponentId msNextMeshComponentId;
		static ComponentId msNextMaterialComponentId;

};

#endif // !COMPONENT_MAN_H
