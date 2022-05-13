#include "AmWanderingVendor.h"
#include "GameMessages.h"
#include "MovementAIComponent.h"
#include "ProximityMonitorComponent.h"
#include "dZoneManager.h"
#include "EntityManager.h"

void AmWanderingVendor::OnStartup(Entity* self) {
	// allows the npc to path (dont ask me why, just have to have it)
	self->SetVar(u"Set.SuspendLuaMovementAI", true);

	const auto* path = dZoneManager::Instance()->GetZone()->GetPath(walkingPath);
	std::vector<NiPoint3> pathWaypoints;
	for (const auto& waypoint : path->pathWaypoints) {
		pathWaypoints.push_back(waypoint.position);
	}
	auto* movementAIComponent = new MovementAIComponent(self, {"wanderingVendor", 0,4,0,0,0});
	movementAIComponent->SetPath(pathWaypoints);
	self->AddComponent(COMPONENT_TYPE_MOVEMENT_AI, movementAIComponent);

	self->SetProximityRadius(interactRadius, "WanderingVendor");
}

void AmWanderingVendor::OnProximityUpdate(Entity* self, Entity* entering, std::string name, std::string status) {
	// Only care about our prox monitor
	if (name != "WanderingVendor") return;
	// Make sure only humans are taken into account
	if (!entering->GetCharacter()) return;

	auto* movementAIComponent = self->GetComponent<MovementAIComponent>();
	if (!movementAIComponent) return;

	if (status == "ENTER" && entering->IsPlayer()) {
		// Make sure the player still exists
		auto* player = EntityManager::Instance()->GetEntity(entering->GetObjectID());
		if (!player) return;
		movementAIComponent->Stop();
	} else if (status == "LEAVE") {
		auto* proximityMonitorComponent = self->GetComponent<ProximityMonitorComponent>();
		if (!proximityMonitorComponent) return;

		m_Counter = 0;
		for (const auto& pair : proximityMonitorComponent->GetProximityObjects("WanderingVendor")) {
			auto* entity = EntityManager::Instance()->GetEntity(pair.first);
			if (entity != nullptr && entity->IsPlayer()) m_Counter++;
		}
		if (m_Counter > 0) return;
		// movementAIComponent->ContinuePathing();
	}
}
