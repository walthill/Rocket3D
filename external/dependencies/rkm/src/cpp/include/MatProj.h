#ifndef MAT_PROJ_H
#define MAT_PROJ_H

#include "Mat4.h"

namespace rkm {
	class MatProj //Matrix Projection Math
	{
			// Help with projection matrices here - http://www.songho.ca/opengl/gl_projectionmatrix.html
			// and here -	http://www.songho.ca/opengl/gl_transform.html#matrix
		public:
			struct ProjectionData //TODO: add documentation code here
			{
				float left, right, bottom, top,
					nearPlaneDistance, farPlaneDistance;
			};

			static Mat4 orthographic(float left, float right, float bottom, float top);

			//*fov should be in RADIANS
			//*aspectRatio should be screen width / screen height
			static Mat4 perspective(float fov, float aspectRatio, float nearPlane, float farPlane); //TODO: comment documentation here
	};
}

#endif // !MAT_PROJ_H
