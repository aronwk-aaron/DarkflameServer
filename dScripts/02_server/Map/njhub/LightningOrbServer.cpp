#include "LightningOrbServer.h"
#include "GameMessages.h"
#include "CombatMessages.h"
#include "EffectsMessages.h"

void LightningOrbServer::OnCollisionPhantom(Entity* self, Entity* target) {
	// Knock whoever touches the orb back the way they came, as live did
	const auto& myPos = self->GetPosition();
	const auto& targetPos = target->GetPosition();

	GameMessages::Knockback knockback;
	knockback.target = target->GetObjectID();
	knockback.Caster = self->GetObjectID();
	knockback.Originator = self->GetObjectID();
	knockback.vector = NiPoint3((targetPos.x - myPos.x) * 2.5f, 15.0f, (targetPos.z - myPos.z) * 2.5f);
	knockback.Send(UNASSIGNED_SYSTEM_ADDRESS);

	GameMessages::PlayFXEffect(self->GetObjectID(), -1, u"knockback", "knockback").Send(UNASSIGNED_SYSTEM_ADDRESS);
}
