#include "EditorMessages.h"
#include "../../core/Editor.h"

#include <render/Camera.h>
#include <core/EngineCore.h>

//TEMP
#include <rkm/Vector3.h>
#include <core/GameObject.h>
#include "../../../RocketEngine/component/TransformComponent.h"

#include <core/Raycast.h>
#include <logging/RK_Log.h>

/*
===========================================================

			Game Key Messages

============================================================
*/

unsigned int EditorKeyDown::id = -1;
GameObject* EditorKeyDown::obj = nullptr;
float EditorKeyDown::angle = 0;

EditorKeyDown::EditorKeyDown(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

EditorKeyDown::~EditorKeyDown()
{
}

//TODO: separate polling input handling (continuous on hold) from callback input handling (single press, single message)

void EditorKeyDown::process(float deltaTime)
{
	Editor* pGameEditor = Editor::getInstance();

	if (pGameEditor != nullptr)
	{
		if (mKeyCode == KEY_Q)
		{
			if (obj == nullptr)
			{
				//TEMP - OBJ CREATION TEST
				TransformData t = { rkm::Vector3(0.0f, 2.1f, -3.0f), rkm::Vector3::one * 0.5f, rkm::Vector3::up, 45.0f };
				MeshComponentData meshData = { "cube", STANDARD_SHADER_KEY, pGameEditor->getRocketEngine()->getShaderManager()->getShaderByKey(STANDARD_SHADER_KEY) };

				obj = pGameEditor->getRocketEngine()->getGameObjectManager()->createGameObject(t, meshData);
				id = obj->getId();
				RK_LOG_C("Creating GameObject -- name: " + obj->name);

				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_E)
		{
			if (obj != nullptr)
			{
				//TEMP - OBJ DELETION TEST
				RK_LOG_C("Destroying GameObject");
				pGameEditor->getRocketEngine()->getGameObjectManager()->destroy(id);
				obj = nullptr;
				pGameEditor->sceneNeedsUpdate();
			}
		}

		if (mKeyCode == KEY_I)
		{
			if (obj != nullptr)
			{
				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX(), pos.getY() + (3 * pGameEditor->getRocketEngine()->deltaTime), pos.getZ());
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_J)
		{
			if (obj != nullptr)
			{
				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX() - (3 * pGameEditor->getRocketEngine()->deltaTime), pos.getY(), pos.getZ());
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_K)
		{
			if (obj != nullptr)
			{

				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX(), pos.getY() - (3 * pGameEditor->getRocketEngine()->deltaTime), pos.getZ());
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_L)
		{
			if (obj != nullptr)
			{
				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX() + (3 * pGameEditor->getRocketEngine()->deltaTime), pos.getY(), pos.getZ());
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_M)
		{
			if (obj != nullptr)
			{
				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX(), pos.getY(), pos.getZ() + (3 * pGameEditor->getRocketEngine()->deltaTime));
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_N)
		{
			if (obj != nullptr)
			{
				rkm::Vector3 pos = obj->getTransform()->getPosition();
				rkm::Vector3 newPos = rkm::Vector3(pos.getX(), pos.getY(), pos.getZ() - (3 * pGameEditor->getRocketEngine()->deltaTime));
				obj->getTransform()->setPosition(newPos);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_T)
		{
			if (obj != nullptr)
			{
				Rotation rot = obj->getTransform()->getRotation();
				rot.angle = angle;
				obj->getTransform()->setRotation(rkm::Vector3::right, rot.angle);
				pGameEditor->sceneNeedsUpdate();
			}
		}
		if (mKeyCode == KEY_W)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraForward(pEngine->deltaTime, true);
		}
		if (mKeyCode == KEY_A)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraLeft(pEngine->deltaTime);
		}
		if (mKeyCode == KEY_S)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraBack(pEngine->deltaTime, true);
		}
		if (mKeyCode == KEY_D)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraRight(pEngine->deltaTime);
		}
		if (mKeyCode == KEY_1)
		{
			pGameEditor->setSceneToNormal();
		}
		if (mKeyCode == KEY_2)
		{
			pGameEditor->setSceneToWireFrame();
		}
	}
}

/*
===========================================================

			Game Mouse DOWN Messages

============================================================
*/

EditorMouseDown::EditorMouseDown(const int& mouseKey, double x, double y)
	:Message(MOUSE_DOWN)
	, mMouseCode(mouseKey)
	, x(x)
	, y(y)
{
}

EditorMouseDown::~EditorMouseDown()
{
}

void EditorMouseDown::process(float deltaTime)
{
	Editor* pGameEditor = Editor::getInstance();

	if (pGameEditor != nullptr)
	{
		if (mMouseCode == LEFT_MOUSE)
		{
			Raycast::calculateScreenRay(x, y);
		}
		if (mMouseCode == RIGHT_MOUSE)
		{
		}
		if (mMouseCode == MIDDLE_MOUSE)
		{
		}
		if (mMouseCode == MOUSE_SCROLL)
		{
			//pGameEditor->getInstance()->getRocketEngine()->getGameCamera()->processMouseScroll((float)y);
		}
	}
}

/*
===========================================================

			Game Mouse MOVE Messages

============================================================
*/

EditorMouseMove::EditorMouseMove(const int& mouseKey, double x, double y)
	:Message(MOUSE_MOVE_TYPE)
	, mMouseMoveCode(mouseKey)
{
	xPos = (float)x;
	yPos = (float)y;
}

EditorMouseMove::~EditorMouseMove()
{
}

void EditorMouseMove::process(float deltaTime)
{
	Editor* pGameEditor = Editor::getInstance();

	if (pGameEditor != nullptr)
	{
		if (mMouseMoveCode == CAM_MOUSE_MOVE) //TODO: make camera speed variable
		{
			pGameEditor->getRocketEngine()->getEditorCamera()->processMouseMovement(deltaTime, xPos, yPos, false);
		}
	}
}
