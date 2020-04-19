#include "EditorMessages.h"
#include "../../core/Editor.h"

#include <render/Camera.h>
#include <core/EngineCore.h>
#include <core/Raycast.h>
#include <logging/RK_Log.h>

/*
===========================================================

			Game Key Messages

============================================================
*/

EditorKeyDown::EditorKeyDown(const int& key)
	:Message(BUTTON_DOWN)
	, mKeyCode(key)
{
}

EditorKeyDown::~EditorKeyDown()
{
}

void EditorKeyDown::process(float deltaTime)
{
	Editor* pGameEditor = Editor::getInstance();

	if (pGameEditor != nullptr)
	{
		if (mKeyCode == ESC)
		{
		}
		if (mKeyCode == KEY_W)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraForward(pEngine->deltaTime * 0.01f);
		}
		if (mKeyCode == KEY_A)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraLeft(pEngine->deltaTime * 0.01f);
		}
		if (mKeyCode == KEY_S)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraBack(pEngine->deltaTime * 0.01f);
		}
		if (mKeyCode == KEY_D)
		{
			EngineCore* pEngine = pGameEditor->getRocketEngine();
			pEngine->getEditorCamera()->moveCameraRight(pEngine->deltaTime * 0.01f);
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
			//Raycast::cast(x,y);
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
