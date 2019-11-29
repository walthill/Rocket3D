#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <RocketMath/Vector3.h>
#include "Component.h"

struct TransformData
{
	struct Rotation
	{
		float angle;
		Vector3 rotationAxis;

		Rotation() : angle(0), rotationAxis(Vector3::up) {}
		Rotation(Vector3 axis, float a) : angle(a), rotationAxis(axis) {}
	};

	Rotation rotation;
	Vector3 position, scale;

	TransformData() : position(Vector3::zero), scale(Vector3::one),
					  rotation() {};
	TransformData(Vector3 pos, Vector3 s, Vector3 rot, float angle) : 
		position(pos), scale(s), rotation(rot, angle) {};
};

const TransformData ZERO_TRANSFORM_DATA;

class TransformComponent : public Component
{
	public:
		TransformComponent(const ComponentId& id);
		~TransformComponent();

		//Getters
		TransformData getData() { return mTransformData; }
		Vector3 getPosition() { return mTransformData.position; };
		Vector3 getScale() { return mTransformData.scale; };
		
		//Setters
		inline void setPosition(Vector3 pos) { mTransformData.position = pos; };
		void setData(const TransformData& data);
		inline void setScale(Vector3 scale) { mTransformData.scale = scale; };
		void setRotation(Vector3 rotationAxis, float angle); //TODO(low): Quaternions?? One day	

	private: 
		TransformData mTransformData;
};

#endif // !TRANSFORM_COMPONENT_H
