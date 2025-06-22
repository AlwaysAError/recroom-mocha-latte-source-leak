#pragma once

namespace Callbacks
{

	bool ForceToolAll() {

		if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
					if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
						Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
					return false;
				}

				for (int i = 0; i < photonPlayerlist.size(); ++i) {
					if (photonPlayerlist[i] != localPlayer.photonPlayer) {
						if (cachedPlayerlist[photonPlayerlist[i]].loadingStage >= LoadingStage::LOADED) {

							const PlayerInfo& targetPlayer = cachedPlayerlist[photonPlayerlist[i]];

							if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
								playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

								PlayerHand* playerHand = globals::jedi::dominantHand ? (PlayerHand*)playerPlayer->get_RightHand() : (PlayerHand*)playerPlayer->get_LeftHand();

								if (playerHand == nullptr) continue;

								const bool& internalDespawnToggle = globals::instantiateAssets::despawnToggle;
								Il2CppString* internalPrefab = il2cpp_string_new_spoof(globals::instantiateAssets::prefab.c_str());
								Vector3& internalScale = globals::instantiateAssets::scale;
								const Vector3 position{ 0.0f, 0.0f, 0.0f };
								constexpr Quaternion rotation{ 0.0f, 0.0f, 0.0f, 0.0f };

								if (globals::instantiateAssets::randomScaleToggle) {
									internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
									internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
									internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
								}

								GameObject* toolObject = PhotonNetwork::photonInstantiate(internalPrefab, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);

								if (toolObject == nullptr) continue;

								auto* toolObjectTool = (Tool*)toolObject->GetComponent("Tool");

								if (toolObjectTool == nullptr) continue;

								playerHand->TryReleaseTool({ 0, 0, 0 }, { 0, 0, 0 });
								playerHand->TryPickupTool(toolObjectTool, false);
							}
						}
					}
				}
			}
			else {
				Log::error("playerlistMutex timed out in ForceToolAll!");
				return false;
			}
		}
		return true;
	}
    
}