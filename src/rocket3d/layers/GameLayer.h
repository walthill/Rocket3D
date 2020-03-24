#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include <render/layers/Layer.h>

class GameApp;

class GameLayer : public Layer
{
	public:
		GameLayer();
		~GameLayer();

		void onUpdate() override;
		
	private:
		GameApp* mpGameInstance;
};


#endif // !GAME_LAYER_H
