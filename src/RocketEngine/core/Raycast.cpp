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

	rkm::Vector4 rayEyeCoords = rkm::Mat4::invert(mpCam->getPerspectiveMatrix()) * rayClipCoordinates;
	rayEyeCoords = rkm::Vector4(rayEyeCoords.getX(), rayEyeCoords.getY(), -1.0f, 0.0f);

	//Step 4: 4d World Coordinates
	
	rkm::Vector3 rayWorldCoords = (rkm::Mat4::invert(mpCam->getViewMatrix()) * rayEyeCoords).xyz();
	rayWorldCoords = rayWorldCoords.normalize();

	std::string printstr = std::to_string(rayWorldCoords.getX());
	RK_CORE_LOG_C(printstr);

	return success;
}
