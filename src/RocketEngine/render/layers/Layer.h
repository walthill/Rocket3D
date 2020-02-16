#ifndef LAYER_H
#define LAYER_H

#include <rkutil/Trackable.h>

class Layer 
{
	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		
		// Returns a bool to allow layers to send result back to the application
		// Currently, quitting the GameApp layer returns false & quits the app
		virtual bool onUpdate() { return false; }
		
		virtual void onEvent() {}

		inline const std::string getLayerName() { return mLayerName; }

	protected:
		std::string mLayerName;
		bool mEnabled;
};

#endif