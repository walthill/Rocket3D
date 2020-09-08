#include "Raycast.h"
#include <rkm/Vector4.h>
#include "../render/Camera.h"
#include "../logging/RK_Log.h"

Camera* Raycast::mpCam = nullptr;

Raycast::Raycast()
{
}

Raycast::~Raycast()
{
}

void Raycast::initEditorRaycast(Camera* camera)
{
	mpCam = camera;
}

bool Raycast::calculateScreenRay(int left, int top, int width, int height, float mouseX, float mouseY)
{
	//TODO: move to camera class
	bool success = false;

	//Step 1: 3d Normalised Device Coordinates
	
	//Starting w/ mouse cursor coords
	//Transform mouse coords into NDCs. A range from [-1, 1]
	//"Scale their range and reverse the direction of y"

	float normalizedX = ((mouseX - left) / (width)) * 2 - 1;
	float normalizedY = 1.0f - 2.0f * (mouseY - top) / (height);
	float normalizedZ = 1.0f;

	if (normalizedX > 1 || normalizedX < -1 || normalizedY > 1 || normalizedY < -1)
		return success;

	//Step 2: 4d Homogeneous Clip Coordinates
	//Make the ray point forward into the scene (negative z direction in OpenGL)

	rkm::Vector4 rayClipCoordinates = rkm::Vector3(normalizedX,
		normalizedY, -normalizedZ);

	//Step 3: 4d Eye (Camera) Coordinates
	// Take the inverse of the projection matrix to move from Clip to Eye coordinates

	rkm::Vector4 rayEyeCoords = rkm::Mat4::invert(mpCam->getPerspectiveMatrix()) * rayClipCoordinates;
	rayEyeCoords = rkm::Vector4(rayEyeCoords.getX(), rayEyeCoords.getY(), rayClipCoordinates.getZ(), 0.0f);

	//Step 4: 4d World Coordinates
	
	rkm::Vector3 rayWorldCoords = (rkm::Mat4::invert(mpCam->getViewMatrix()) * rayEyeCoords).xyz();
	rayWorldCoords = rayWorldCoords.normalize();

	return success;
}
