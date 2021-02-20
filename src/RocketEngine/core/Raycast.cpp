#include "Raycast.h"
#include "../render/Camera.h"
#include "../window/Window.h"
#include "../../Rocket3d/core/Application.h"
#include "../logging/RK_Log.h"

Camera* Raycast::mpCam = nullptr;

//GLM intersect solution? https://glm.g-truc.net/0.9.0/api/a00162.html#a33f0584acca58d7446daf594c3b8295f
//Mouse picking ray collision w/ code sample https://community.khronos.org/t/mouse-picking-with-opengl/76055

//extra just in case https://gamedev.stackexchange.com/questions/6940/3d-ray-casting-picking

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

rkm::Vector3 Raycast::calculateScreenRay(float mouseX, float mouseY)
{
	//TODO: move to camera class?
	rkm::Vector3 rayDirection = rkm::Vector3::zero;

	ImGuiLayer* wind = Application::getInstance()->getEditor();
	float left = wind->getEditorWindowPos().getX() + msLeftOffset;
	float top = wind->getEditorWindowPos().getY() + msTopOffset;
	float width = wind->getEditorWindowDimensions().getX() - msWidthOffset;
	float height = wind->getEditorWindowDimensions().getY() - msHeightOffset;
	
	//Step 1: 3d Normalised Device Coordinates
	//Starting w/ mouse cursor coords
	//Transform mouse coords into NDCs. A range from [-1, 1]
	//"Scale their range and reverse the direction of y"
	float normalizedX = ((mouseX - left) / (width)) * 2 - 1;
	float normalizedY = 1.0f - 2.0f * (mouseY - top) / (height);
	float normalizedZ = 1.0f;

	if (normalizedX > 1 || normalizedX < -1 || normalizedY > 1 || normalizedY < -1)
		return rayDirection;

	//Step 2: 4d Homogeneous Clip Coordinates
	//Make the ray point forward into the scene (negative z direction in OpenGL)
	rkm::Vector4 rayClipCoordinates = rkm::Vector3(normalizedX,
		normalizedY, -normalizedZ);

	//Step 3: 4d Eye (Camera) Coordinates
	// Take the inverse of the projection matrix to move from Clip to Eye coordinates
	rkm::Vector4 rayEyeCoords = rkm::Mat4::invert(mpCam->getPerspectiveMatrix()) * rayClipCoordinates;
	rayEyeCoords = rkm::Vector4(rayEyeCoords.getX(), rayEyeCoords.getY(), -1.0f, 0.0f);

	//Step 4: 4d World Coordinates	
	rkm::Vector3 rayWorldCoords = (rkm::Mat4::invert(mpCam->getViewMatrix()) * rayEyeCoords).xyz();
	rayDirection = rayWorldCoords.normalize();

	return rayDirection;
}
