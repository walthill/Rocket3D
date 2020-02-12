#include "LayerStack.h"

LayerStack::LayerStack()
{
	mLayerInsert = mLayerStack.begin();
}

LayerStack::~LayerStack()
{
	for (auto layer : mLayerStack)
		delete layer;
}

void LayerStack::pushLayer(Layer* layer)
{
	mLayerInsert = mLayerStack.emplace(mLayerInsert, layer);
}

void LayerStack::pushOverlay(Layer* overlay)
{
	mLayerStack.emplace_back(overlay);
}

void LayerStack::popLayer(Layer* layer)
{
	auto it = std::find(mLayerStack.begin(), mLayerStack.end(), layer);
	if (it != mLayerStack.end())
	{
		mLayerStack.erase(it);
		mLayerInsert -= 1;
	}
}

void LayerStack::popOverlay(Layer* overlay)
{
	auto it = std::find(mLayerStack.begin(), mLayerStack.end(), overlay);
	if (it != mLayerStack.end())
	{
		mLayerStack.erase(it);
	}
}
