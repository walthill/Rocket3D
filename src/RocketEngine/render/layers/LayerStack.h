#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <vector>
#include "Layer.h"

//Wrapper for vector of layers
class LayerStack
{
	//Layers render front to back. Layers at the start of the stack are rendered behind the ensuing layers
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);	//render overlays last
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		//allows for use in a range-based for loop
		std::vector<Layer*>::iterator begin() { return mLayerStack.begin(); }
		std::vector<Layer*>::iterator end() { return mLayerStack.end(); }

	private:
		std::vector<Layer*> mLayerStack;
		unsigned int mLayerInsertIndex = 0; //tracks point at which to insert layer
};

#endif // !LAYER_STACK_H
