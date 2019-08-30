/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of tutorials from Learn OpenGL
	(https://learnopengl.com)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 Camera.h
	=========================
	The camera class is moved by the use to change the view of the 3d game world

********/

#ifndef CAMERA_H
#define CAMERA_H

#include <RocketMath/MathUtils.h>
#include <DeanLib/Trackable.h>

class Camera : public Trackable
{
	//Help from Learn OpenGL code https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

	public:

		/***
			* Constructor initializes camera member variables from paramters
			* Calculates Front, Right, and Up for the camera
		***/
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
		/* Empty deconstructor */
		~Camera() {};

		/***
			* Calculates mouse movement and converts params into a new camera position
		***/
		void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true)
		{
			xOffset *= mMouseSensitivity;
			yOffset *= mMouseSensitivity;

			mYaw += xOffset;
			mPitch += yOffset;

			//First-person camera -- limit ability to look up and down
			if(constrainPitch)
				mPitch = RK_Math::clamp(mPitch, -89.0f, 89.0f);

			updateCameraVectors();
		};



		/***
			* Camera can zoom in/out
		***/		
		void processMouseScroll(float yOffset)
		{
			if (mZoom >= 1.0f && mZoom <= 45.0f)
				mZoom -= yOffset;

			mZoom = RK_Math::clamp(mZoom, 1.0f, 45.0f);
		};

		/***
			* Access the camera's view matrix
		***/
		Mat4 getViewMatrix() { return Mat4::lookAt(mPos, mPos + mFront, mUp); };
		
		/***
			* Move camera left
		***/
		void moveCameraLeft(float deltaTime) { mPos -= mRight * mMoveSpeed * deltaTime; };
		
		/***
			* Move camera right
		***/
		void moveCameraRight(float deltaTime) { mPos += mRight * mMoveSpeed * deltaTime; };

		/*
			BenjiHor  @ Learn OpenGl - https://learnopengl.com/Getting-started/Camera
			
			I had this same problem. 
			I realized that moving forward/backward should be dependent 
			on the up vector with respect to the world and the right vector 
			with respect to the camera.

			So the code may look something along the lines of 
			position += glm::normalize(glm::cross(world_up, camera_right));
		*/

		/***
			* Move camera forward
		***/
		void moveCameraForward(float deltaTime) 
		{ 
			mPos += Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
	//		mPos += Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
		};
		
		/***
			* Move camera back
		***/
		void moveCameraBack(float deltaTime)
		{ 
			mPos -= Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
//			mPos -= Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
		};

		/***
			* Access camera front vector
		***/
		Vector3* getFront() { return &mFront; };
		/***
			* Access camera FOV
		***/
		float getFov() { return mZoom; };
		/***
			* Access camera position vector
		***/
		Vector3* getPosition() { return &mPos; };

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


		/***
			* Calculate camera position and rotation
		***/
		void updateCameraVectors()
		{
			Vector3 front;
			front = Vector3(
				cos(RK_Math::degToRad(mYaw)) * cos(RK_Math::degToRad(mPitch)),
				sin(RK_Math::degToRad(mPitch)),
				sin(RK_Math::degToRad(mYaw)) * cos(RK_Math::degToRad(mPitch)));

			mFront = front.normalize();

			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			mRight = Vector3::cross(mFront, mWorldUp).normalize();
			mUp = Vector3::cross(mRight, mFront).normalize();
		};
};

#endif // !CAMERA_H
