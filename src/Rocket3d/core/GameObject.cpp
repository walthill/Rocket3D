#include "GameObject.h"
#include "GameApp.h"
#include "../component/ComponentManager.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	destroy();
}


void GameObject::destroy()
{
}

void GameObject::render()
{
	MeshComponent*  meshComponent = getMesh();
	if(meshComponent != nullptr) 
	{
		TransformData data = mpTransform->getData();
		
		meshComponent->render(data.position, data.scale,
							  data.rotation.rotationAxis, data.rotation.angle);
	}
}

MeshComponent * GameObject::getMesh()
{
	MeshComponent* pComponent = GameApp::getInstance()->getComponentManager()->getMeshComponent(mMeshId);
	return pComponent;
}
