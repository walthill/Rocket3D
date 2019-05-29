#ifndef LIGHT_H
#define LIGHT_H

#include <RocketMath/Vector3.h>

class RK_Shader;

class Light
{
	public:
		Light(Vector3 amb, Vector3 diff, Vector3 spec) { mAmbientLight = amb; mDiffuseLight = diff; mSpecularLight = spec; };

		virtual void processLightingData(RK_Shader* man) = 0;

		void setAmbientVector(Vector3 vec) { mAmbientLight = vec; };
		void setDiffuseVector(Vector3 vec) { mDiffuseLight = vec; };
		void setSpecularVector(Vector3 vec) { mSpecularLight = vec; };

		const Vector3*  getAmbientVector() const { return &mAmbientLight; };
		const Vector3*  getDiffuseVector() const { return &mDiffuseLight; };
		const Vector3*  getSpecularVector() const { return &mSpecularLight; };

	protected:
		Vector3 mAmbientLight, mDiffuseLight, mSpecularLight;

	private:
		
};

#endif // !LIGHT_H
