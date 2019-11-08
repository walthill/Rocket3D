#include "GameObject.h"
#include "../component/MaterialComponent.h"
#include "../component/MeshComponent.h"
#include <RocketMath/Vector3.h>

GameObject::GameObject(MeshComponent* mesh, MaterialComponent* material)
{
	mTransform = {};
	mTransform.position = Vector3::zero;
	mTransform.rotation.angle = 0;
	mTransform.rotation.rotationAxis = Vector3::one;
	mTransform.scale = Vector3::one;

	if (material != nullptr)
	{
		mMaterial = material;
	}

	if (mesh != nullptr)
	{
		mMesh = mesh;
		mMesh->linkMaterialComponent(mMaterial);
	}

}

GameObject::~GameObject()
{
	destroy();
}


void GameObject::destroy()
{
	delete mMaterial;
	delete mMesh;
}

void GameObject::update()
{
}

void GameObject::render()
{
	mMesh->render(mTransform.position, mTransform.scale, 
				  mTransform.rotation.rotationAxis, mTransform.rotation.angle);
}

void GameObject::setRotation(Vector3 rotationAxis, float angle)
{
	mTransform.rotation.rotationAxis = rotationAxis;
	mTransform.rotation.angle = angle;
}
