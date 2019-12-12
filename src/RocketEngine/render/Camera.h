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

#include <rkm/MathUtils.h>
#include <rkutil/Trackable.h>

class Camera : public rkutil::Trackable
{
	//Help from Learn OpenGL code https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

	public:

		/***
			* Constructor initializes camera member variables from paramters
			* Calculates Front, Right, and Up for the camera
		***/
		Camera(rkm::Vector3 position = rkm::Vector3::zero, rkm::Vector3 up = rkm::Vector3::up, float yaw = -90.0f, float pitch = 0.0f)
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
		void processMouseMovement(float deltaTime, float xOffset, float yOffset, bool constrainPitch = true)
		{
			xOffset *= mMouseSensitivity;
			yOffset *= mMouseSensitivity;

			mYaw += xOffset;
			mPitch += yOffset; 

			//First-person camera -- limit ability to look up and down
			if(constrainPitch)
				mPitch = rkm::clamp(mPitch, -89.0f, 89.0f);

			updateCameraVectors();
		};



		/***
			* Camera can zoom in/out
		***/		
		void processMouseScroll(float yOffset)
		{
			if (mZoom >= 1.0f && mZoom <= 45.0f)
				mZoom -= yOffset;

			mZoom = rkm::clamp(mZoom, 1.0f, 45.0f);
		};

		/***
			* Access the camera's view matrix
		***/
		rkm::Mat4 getViewMatrix() { return rkm::Mat4::lookAt(mPos, mPos + mFront, mUp); };
		
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
			mPos += rkm::Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
	//		mPos += Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
		};
		
		/***
			* Move camera back
		***/
		void moveCameraBack(float deltaTime)
		{ 
			mPos -= rkm::Vector3::cross(mUp, mRight).normalize() * mMoveSpeed * deltaTime;
//			mPos -= Vector3::cross(mWorldUp, mRight).normalize() * mMoveSpeed * deltaTime;
		};

		/***
			* Access camera front vector
		***/
		rkm::Vector3* getFront() { return &mFront; };
		/***
			* Access camera FOV
		***/
		float getFov() { return mZoom; };
		/***
			* Access camera position vector
		***/
		rkm::Vector3* getPosition() { return &mPos; };

	private:
		// Camera Attributes
		rkm::Vector3 mPos;
		rkm::Vector3 mFront;
		rkm::Vector3 mUp;
		rkm::Vector3 mRight;
		rkm::Vector3 mWorldUp = rkm::Vector3::up;

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
			rkm::Vector3 front;
			front = rkm::Vector3(
				cos(rkm::degToRad(mYaw)) * cos(rkm::degToRad(mPitch)),
				sin(rkm::degToRad(mPitch)),
				sin(rkm::degToRad(mYaw)) * cos(rkm::degToRad(mPitch)));

			mFront = front.normalize();

			// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
			mRight = rkm::Vector3::cross(mFront, mWorldUp).normalize();
			mUp = rkm::Vector3::cross(mRight, mFront).normalize();
		};
};

#endif // !CAMERA_H
