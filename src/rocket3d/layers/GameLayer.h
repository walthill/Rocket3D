#ifndef GAME_LAYER_H
#define GAME_LAYER_H

#include <render/layers/Layer.h>

class GameLayer : public Layer
{
	public:
		GameLayer();
		~GameLayer();

		bool onUpdate() override;
};


#endif // !GAME_LAYER_H