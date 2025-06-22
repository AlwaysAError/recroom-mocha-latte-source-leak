#pragma once

void StaticFly() {
	bool internalStaticFlyToggle = globals::staticFlyToggle;

	if (internalStaticFlyToggle) { // this is terrible code. crashes. i dont care.

		if ((localPlayer.loadingStage >= LoadingStage::LOADED) && RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)->get_IsInitialized()) {

			RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

			void* localPlayerPlayerMovement = localPlayerPlayer->get_PlayerMovement();

			typedef bool (*get_IsFlyingEnabled_t)(void* instance);
			get_IsFlyingEnabled_t isFlyingEnabled = (get_IsFlyingEnabled_t)(methods::RecRoomCoreLocomotion::PlayerMovement::get_IsFlyingEnabled);

			if (!isFlyingEnabled(localPlayerPlayerMovement)) {

				AddFlyEnabled_t AddFlyEnabled = (AddFlyEnabled_t)(methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled);

				AddFlyEnabled(localPlayerPlayerMovement, true, (Il2CppObject*)PlayerGameRoleManager::get_Instance(), TEST, nullptr); // TEST is int limit for some reason lmfao
			}
		}
	}
}