#include "include/MatProj.h"

namespace rkm {
	
	Mat4 MatProj::orthographic(float left, float right, float bottom, float top)
	{
		float projArr[16] = { 0 };

		//Diagonal transformations (1, 5, 10 in column major)
		projArr[0] = 2 / (right - left);
		projArr[5] = 2 / (top - bottom);
		projArr[10] = -1;
		projArr[15] = 1;

		//Bottom left transformations (3,7 in column major)
		projArr[3] = -(right + left) / (right - left);
		projArr[7] = -(top + bottom) / (top - bottom);

		return Mat4(projArr);
	}

	//*fov should be in RADIANS
	//*aspectRatio should be screen width / screen height
	Mat4 MatProj::perspective(float fov, float aspectRatio, float nearPlane, float farPlane) //TODO: comment documentation here
	{
		float projArr[16] = { 0 };

		//Generate projection data
		float height = nearPlane * tan(fov / 2);
		float width = height * aspectRatio;

		ProjectionData data = { -width, width, -height, height, nearPlane, farPlane };

		//Diagonal transformations
		projArr[0] = 2 * data.nearPlaneDistance / (data.right - data.left);
		projArr[5] = 2 * data.nearPlaneDistance / (data.top - data.bottom);
		projArr[10] = -((data.farPlaneDistance + data.nearPlaneDistance) / (data.farPlaneDistance - data.nearPlaneDistance));
		projArr[15] = 0;

		//3rd column
		projArr[2] = (data.right + data.left) / (data.right - data.left);
		projArr[6] = (data.top + data.bottom) / (data.top - data.bottom);
		projArr[14] = -1;

		projArr[11] = -2 * data.farPlaneDistance * data.nearPlaneDistance / (data.farPlaneDistance - data.nearPlaneDistance);

		return Mat4(projArr);
	}
}