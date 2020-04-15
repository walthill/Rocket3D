#include "Raycast.h"
#include <rkm/Vector4.h>

Raycast::Raycast()
{
}

Raycast::~Raycast()
{
}

bool Raycast::cast(int width, int height, float mouseX, float mouseY)
{
	bool success = false;

	//Step 1: 3d Normalised Device Coordinates
	
	//Starting w/ mouse cursor coords
	//Transform mouse coords into NDCs. A range from [-1, 1]
	//"Scale their range and reverse the direction of y"

	float x = (2.0f * mouseX) / width - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / height;
	float z = 1.0f;

	rkm::Vector3 rayNormalizedDeviceCoords = rkm::Vector3(x, y, z);

	//Step 2: 4d Homogeneous Clip Coordinates
	//Make the ray point forward into the scene (negative z direction in OpenGL)

	rkm::Vector4 rayClipCoordinates = rkm::Vector3(rayNormalizedDeviceCoords.getX(),
		rayNormalizedDeviceCoords.getY(), -1.0f);

	//Step 3: 4d Eye (Camera) Coordinates
	// Take the inverse of the projection matrix to move from Clip to Eye coordinates

//	rkm::Vector4 rayEyeCoordinates = rkm

	return success;
}
