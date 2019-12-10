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

void GameObject::update(float elapsedTime)
{
	if (mpTransform->hasChanged())
	{
		MeshComponent* meshComponent = getMesh();
		if (meshComponent != nullptr)
		{
			TransformData data = mpTransform->getData();

			meshComponent->process(data.position, data.scale,
				data.rotation.rotationAxis, data.rotation.angle);
		}

		mpTransform->setHasChanged(false);
	}
}

void GameObject::render()
{
}

MeshComponent * GameObject::getMesh()
{
	auto pComponent = GameApp::getInstance()->getComponentManager()->getMeshComponent(mMeshId);
	return pComponent;
}

MaterialComponent* GameObject::getMaterial()
{
	//auto pComponent = GameApp::getInstance()->getComponentManager()->getMaterialComponent(mMaterialId);
	return nullptr;
}

SpotLightComponent* GameObject::getSpotLight()
{
	auto pComponent = GameApp::getInstance()->getComponentManager()->getSpotlightComponent(mSpotLightId);
	return pComponent;
}

DirectionalLightComponent* GameObject::getDirectionalLight()
{
	auto pComponent = GameApp::getInstance()->getComponentManager()->getDirectionalLightComponent(mDirectionalLightId);
	return pComponent;
}

PointLightComponent* GameObject::getPointLight()
{
	auto pComponent = GameApp::getInstance()->getComponentManager()->getPointLightComponent(mPointLightId);
	return pComponent;
}
