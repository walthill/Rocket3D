#ifndef CAMERA_H
#define CAMERA_H

#include <RocketMath/MathUtils.h>

class Camera
{
	//Help from Learn OpenGL code https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

	public:
		Camera(Vector3 position = Vector3::zero, Vector3 up = Vector3::up, float yaw = -90.0f, float pitch = 0.0f) 
		{
			mMoveSpeed = 2.5f;
			mMouseSensitivity = 0.1f;
			mZoom = 45.0f;

			mPos = position;
			mWorldUp = up;
			mYaw = yaw;
			mPitch = pitch;
			updateCameraVectors();
		};
		
		~Camera() {};

		void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true)
		{
			xOffset *= mMouseSensitivity;
			yOffset *= mMouseSensitivity;

			mYaw += xOffset;
			mPitch += yOffset;

			if(constrainPitch)
				mPitch = R3_Math::clamp(mPitch, -89.0f, 89.0f);

			updateCameraVectors();
		};

		void processMouseScroll(float yOffset)
		{
			if (mZoom >= 1.0f && mZoom <= 45.0f)
				mZoom -= yOffset;

			mZoom = R3_Math::clamp(mZoom, 1.0f, 45.0f);
		};

		Mat4 getViewMatrix() { return Mat4::lookAt(mPos, mPos + mFront, mUp); };
		float getFov() { return mZoom; };
		
		void moveCameraLeft(float deltaTime) 
		{ 
			mPos -= mRight * mMoveSpeed * deltaTime;
			mPos = Vector3(mPos.getX(), 0.0f, mPos.getZ());

		};

		void moveCameraRight(float deltaTime) 
		{ 
			mPos += mRight * mMoveSpeed * deltaTime;
			mPos = Vector3(mPos.getX(), 0.0f, mPos.getZ());

		};

		/*
			BenjiHor  @ Learn OpenGl - https://learnopengl.com/Getting-started/Camera
			
			I had this same problem. 
			I realized that moving forward/backward should be dependent 
			on the up vector with respect to the world and the right vector 
			with respect to the camera.

			So the code may look something along the lines of 
			position += glm::normalize(glm::cross(world_up, camera_right));
		*/

		void moveCameraForward(float deltaTime) 
		{ 
			mPos += Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
			mPos = Vector3(mPos.getX(), 0.0f, mPos.getZ());
		};
		
		void moveCameraBack(float deltaTime) 
		{ 
			mPos -= Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
			mPos = Vector3(mPos.getX(), 0.0f, mPos.getZ());
		};

	private:
		// Camera Attributes
		Vector3 mPos;
		Vector3 mFront;
		Vector3 mUp;
		Vector3 mRight;
		Vector3 mWorldUp = Vector3::up;

		// Euler Angles
		float mYaw;
		float mPitch;

		// Camera options
		float mMoveSpeed = 2.5f;
		float mMouseSensitivity = 0.1f;
		float mZoom = 45.0f;

		void updateCameraVectors()
		{
			Vector3 front;
			front = Vector3(
				cos(R3_Math::degToRad(mYaw)) * cos(R3_Math::degToRad(mPitch)),
				sin(R3_Math::degToRad(mPitch)),
				sin(R3_Math::degToRad(mYaw)) * cos(R3_Math::degToRad(mPitch)));

			mFront = front.normalize();

			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			mRight = Vector3::cross(mFront, mWorldUp).normalize();
			mUp = Vector3::cross(mRight, mFront).normalize();
		};
};

#endif // !CAMERA_H
