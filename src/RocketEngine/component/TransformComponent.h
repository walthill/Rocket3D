/********
	=========================
			 ROCKET3D
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
		 TransformComponent.h
	=========================
	This file contains the definition for the Transform Component object.
	Inlucdes info for Transform data and manipulation of position, scale, and rotation

********/

#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include <rkm/Vector3.h>
#include "Component.h"

struct Rotation
{
	float angle;			///< Rotation angle
	rkm::Vector3 rotationAxis;	///< Axis of rotation

	///Default constructor sets all values to zero
	Rotation() : angle(0), rotationAxis(rkm::Vector3::up) {}
	///Constructor that takes in values for struct variables
	Rotation(rkm::Vector3 axis, float a) : angle(a), rotationAxis(axis) {}
};


/***************************************************************************//**
 * @brief 	Data used in every transform component.
 *
 * This struct contains data and constructors that will serve as foundational data
 * for every gameobject's transform
 ******************************************************************************/
struct TransformData
{
	/*struct Rotation
	{
		float angle;			///< Rotation angle
		rkm::Vector3 rotationAxis;	///< Axis of rotation

		///Default constructor sets all values to zero
		Rotation() : angle(0), rotationAxis(rkm::Vector3::up) {}
		///Constructor that takes in values for struct variables
		Rotation(rkm::Vector3 axis, float a) : angle(a), rotationAxis(axis) {}
	};
	*/
	Rotation rotation;	///< Transform rotation data
	rkm::Vector3 position;	///< Transform position value
	rkm::Vector3 scale;		///< Transform scale value

	///Default constructor sets all values to zero
	TransformData() : position(rkm::Vector3::zero), scale(rkm::Vector3::one), rotation() {};

	///Constructor that takes in values for struct variables
	TransformData(rkm::Vector3 pos, rkm::Vector3 s, rkm::Vector3 rot, float angle) : position(pos), scale(s), rotation(rot, angle) {};
};

const TransformData ZERO_TRANSFORM_DATA;

/***************************************************************************//**
 * @brief 	The component for GameObject transforms.
 *
 * This class, derived from Component, contains data and flags needed to
 * render and manipulate GameObjects.
 ******************************************************************************/
class TransformComponent : public Component
{
	public:

		/**********************************************************************//**
		* Creates component with the given id value.
		*
		* @param id ComponentId value assigned to this instance of the Component class
		*************************************************************************/
		TransformComponent(const ComponentId& id);

		///Default deconstructor
		~TransformComponent();

		///Access the transform component data
		TransformData getData() { return mTransformData; }
		///Access the transform component position
		rkm::Vector3 getPosition() { return mTransformData.position; };
		///Access the transform component scale
		rkm::Vector3 getScale() { return mTransformData.scale; };
		///Access the transform component rotation data
		Rotation getRotation() { return mTransformData.rotation; };
		///Check if the transform component data has changed
		bool hasChanged() { return mDataChanged; }

		/**********************************************************************//**
		 * Set position value
		 *
		 * @param pos New position vector
		 *************************************************************************/
		void setPosition(rkm::Vector3 pos);

		/**********************************************************************//**
		 * Set position value
		 *
		 * @param data TransformData struct with data to store in the component
		 *************************************************************************/
		void setData(const TransformData& data);

		/**********************************************************************//**
		 * Set position value
		 *
		 * @param pos New position vector
		 *************************************************************************/
		void setScale(rkm::Vector3 scale);

		/**********************************************************************//**
		 * Set rotation value
		 *
		 * @param pos New rotation axis vector 
		 * @param angle New rotation angle 
		 *************************************************************************/
		void setRotation(rkm::Vector3 rotationAxis, float angle); //TODO(low): Quaternions?? One day	

		/**********************************************************************//**
		 * Set mDataChanged flag
		 *
		 * @param changed Boolean to switch mDataChanged flag.
		 *************************************************************************/
		void setHasChanged(bool changed) { mDataChanged = changed; }

	private: 
		TransformData mTransformData;
		bool mDataChanged = false;
};

#endif // !TRANSFORM_COMPONENT_H
