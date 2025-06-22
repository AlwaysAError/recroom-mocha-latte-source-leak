#pragma once

enum class ReleaseType : int // HOENEBDPIHE
{
	Unknown1 = 0,
	Manual = 1,
	Automatic = 2,
};

struct Tool : Component {};

struct PlayerHand : MonoBehaviourPun {

	typedef bool (*TryReleaseTool_t)(PlayerHand* instance, Vector3 releaseVelocity, Vector3 releaseAngularVelocity, ReleaseType type);
	bool TryReleaseTool(Vector3 releaseVelocity, Vector3 releaseAngularVelocity, ReleaseType type = ReleaseType::Automatic) {
		const auto func = (TryReleaseTool_t)(methods::PlayerHand::TryReleaseTool);
		return func(this, releaseVelocity, releaseAngularVelocity, type);
	}

	typedef bool (*TryPickupTool_t)(PlayerHand* instance, Tool* tool, bool targetedInPrecisePhase, bool forceSnapPosition);
	bool TryPickupTool(Tool* tool, bool targetedInPrecisePhase, bool forceSnapPosition = false) {
		const auto func = (TryPickupTool_t)(methods::PlayerHand::TryPickupTool);
		return func(this, tool, targetedInPrecisePhase, forceSnapPosition);
	}

};