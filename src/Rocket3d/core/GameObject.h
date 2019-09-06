#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <RocketMath/Vector3.h>

class MaterialComponent;
class MeshComponent;


struct Transform
{
	struct Rotation
	{
		float angle;
		Vector3 rotationAxis;
	} rotation;
	
	Vector3 position, scale;
};

class GameObject : public Trackable 
{
	public:
		GameObject(MeshComponent* mesh = nullptr, MaterialComponent* material = nullptr);
		~GameObject();

		void destroy();

		void update();
		void render();

		void setPosition(Vector3 pos);
		void setScale(Vector3 scale);
		void setRotation(Vector3 rotationAxis, float angle); //TODO(low): Quaternions??

	private:
		void setScale();

		Transform mTransform;
		MeshComponent* mMesh;
		MaterialComponent* mMaterial;
};

#endif // !GAME_OBJ_H
