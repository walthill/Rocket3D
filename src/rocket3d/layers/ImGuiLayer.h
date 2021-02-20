#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <rkm/Vector2.h>
#include "../../RocketEngine/render/layers/Layer.h"

//TODO: seperate layer code into more organized objects

class ImGuiLayer : public Layer
{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onImGuiRender() override;

		void begin();
		void end();	

		void drawDockSpace();
		void drawToolbar();
		void drawSceneTree();
		void drawInspector();
		void drawGameWindow();
		void drawEditorWindow();

		rkm::Vector2 getEditorWindowDimensions();
		rkm::Vector2 getEditorWindowPos();

	private:
		float mTime = 0.0f;

		float mEditorWindowWidth, mEditorWindowHeight;
		rkm::Vector2 mEditorPos;

		void* mGameWindowTexture;
};

#endif // !IMGUI_LAYER_H
