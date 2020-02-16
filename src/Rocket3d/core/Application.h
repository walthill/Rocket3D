#ifndef APP_H
#define APP_H

#include <render/layers/LayerStack.h>
#include <logging/RK_Log.h>
#include "GameApp.h"

//Event system? for layer-unique inputs


class Application
{
	public:
		Application();
		~Application();

		void init();

		void addLayer(Layer* layer);
		void addOverlay(Layer* overlay);

		void run();

	private:
		LayerStack mLayerStack;
		bool mIsRunning;
};

#endif // !APP_H
