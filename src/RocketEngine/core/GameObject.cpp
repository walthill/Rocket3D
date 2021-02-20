#include "GameObject.h"
#include "../../Rocket3d/core/GameApp.h"
#include "EngineCore.h"

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
	auto pComponent = GameApp::getInstance()->getRocketEngine()->getComponentManager()->getMeshComponent(mMeshId);
	return pComponent;
}

//MaterialComponent* GameObject::getMaterial()
//{
	//auto pComponent = GameApp::getInstance()->getComponentManager()->getMaterialComponent(mMaterialId);
//	return nullptr;
//}

SpotLightComponent* GameObject::getSpotLight()
{
	auto pComponent = GameApp::getInstance()->getRocketEngine()->getComponentManager()->getSpotlightComponent(mSpotLightId);
	return pComponent;
}

DirectionalLightComponent* GameObject::getDirectionalLight()
{
	auto pComponent = GameApp::getInstance()->getRocketEngine()->getComponentManager()->getDirectionalLightComponent(mDirectionalLightId);
	return pComponent;
}

PointLightComponent* GameObject::getPointLight()
{
	auto pComponent = GameApp::getInstance()->getRocketEngine()->getComponentManager()->getPointLightComponent(mPointLightId);
	return pComponent;
}
