#pragma once
#include "CppScripts.h"

class AmWanderingVendor : public CppScripts::Script {
	public:
		void OnStartup(Entity* self);
		void OnProximityUpdate(Entity* self, Entity* entering, std::string name, std::string status);
		auto* movementAIComponent = new MovementAIComponent(self, movementInfo);
		self->AddComponent(COMPONENT_TYPE_MOVEMENT_AI, movementAIComponent);
	private:
		std::string walkingPath = "CartVendorPath";
		float interactRadius = 10.0f;
		int m_Counter;
};
