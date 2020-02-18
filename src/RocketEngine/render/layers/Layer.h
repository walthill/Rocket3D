#ifndef LAYER_H
#define LAYER_H

#include <rkutil/Trackable.h>

class Layer : public rkutil::Trackable
{
	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}		
		virtual void onUpdate() {}
		virtual void onEvent() {}

		inline const std::string getLayerName() { return mLayerName; }

	protected:
		std::string mLayerName;
		bool mEnabled;
};

#endif