#include "TransformComponent.h"

TransformComponent::TransformComponent(const ComponentId & id) :
	Component(id)
{
}

TransformComponent::~TransformComponent()
{
}

inline void TransformComponent::setPosition(rkm::Vector3 pos)
{
	mTransformData.position = pos;
	mDataChanged = true;
}

void TransformComponent::setData(const TransformData & data)
{
	mTransformData.position = data.position;
	mTransformData.rotation.angle = data.rotation.angle;
	mTransformData.rotation.rotationAxis = data.rotation.rotationAxis;
	mTransformData.scale = data.scale;
	mDataChanged = true;
}

inline void TransformComponent::setScale(rkm::Vector3 scale)
{
	mTransformData.scale = scale;
	mDataChanged = true;
}

void TransformComponent::setRotation(rkm::Vector3 rotationAxis, float angle)
{
	mTransformData.rotation.angle = angle;
	mTransformData.rotation.rotationAxis = rotationAxis;
	mDataChanged = true;
}
