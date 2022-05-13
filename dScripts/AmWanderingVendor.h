#pragma once
#include "CppScripts.h"


class AmWanderingVendor : public CppScripts::Script {
	public:
		void OnStartup(Entity* self);
		void OnProximityUpdate(Entity* self, Entity* entering, std::string name, std::string status);
	private:
		std::string walkingPath = "CartVendorPath";
		float interactRadius = 10.0f;
		int m_Counter;
};
