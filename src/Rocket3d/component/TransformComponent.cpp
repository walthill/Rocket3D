#include "TransformComponent.h"

TransformComponent::TransformComponent(const ComponentId & id) :
	Component(id)
{
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::setData(const TransformData & data)
{
	mTransformData.position = data.position;
	mTransformData.rotation.angle = data.rotation.angle;
	mTransformData.rotation.rotationAxis = data.rotation.rotationAxis;
	mTransformData.scale = data.scale;
}
