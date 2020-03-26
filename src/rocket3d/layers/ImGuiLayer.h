#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "../../RocketEngine/render/layers/Layer.h"

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

	private:
		float mTime = 0.0f;

		void* mGameWindowTexture;
};

#endif // !IMGUI_LAYER_H
