#include "Camera.h"

Camera::Camera(rkm::Vector3 position, rkm::Vector3 up, float yaw, float pitch)
{
	mMoveSpeed = 2.5f;
	mMouseSensitivity = 0.1f;
	mZoom = 45.0f;

	mPos = position;
	mWorldUp = up;
	mYaw = yaw;
	mPitch = pitch;
	updateCameraVectors();
}

void Camera::processMouseMovement(float deltaTime, float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= mMouseSensitivity;
	yOffset *= mMouseSensitivity;

	mYaw += xOffset;
	mPitch += yOffset;

	//First-person camera -- limit ability to look up and down
	if (constrainPitch)
		mPitch = rkm::clamp(mPitch, -89.0f, 89.0f);

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset)
{
	if (mZoom >= 1.0f && mZoom <= 45.0f)
		mZoom -= yOffset;

	mZoom = rkm::clamp(mZoom, 1.0f, 45.0f);
}

void Camera::moveCameraLeft(float deltaTime)
{
	mPos -= mRight * mMoveSpeed * deltaTime;
}

void Camera::moveCameraRight(float deltaTime)
{
	mPos += mRight * mMoveSpeed * deltaTime;
}

void Camera::moveCameraForward(float deltaTime)
{
	mPos += rkm::Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
	//mPos += Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
}

void Camera::moveCameraBack(float deltaTime)
{
	mPos -= rkm::Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
	//mPos -= Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
}


