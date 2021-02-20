#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include <render/layers/Layer.h>
#include "../core/Editor.h"
#include "../core/GameApp.h"

class GameLayer : public Layer
{
	public:
		GameLayer();
		~GameLayer();

		void onUpdate() override;
		
	private:
		GameApp* mpGameInstance;
		Editor* mpEditorInstance;
};


#endif // !GAME_LAYER_H
