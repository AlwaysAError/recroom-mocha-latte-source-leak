#pragma once

namespace Callbacks
{
	bool SpawnAssetAll() {

		std::unique_lock lock(playerlistMutex, std::defer_lock);

		if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

			if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::RECROOM)
			{
				for (int i = 0; i < photonPlayerlist.size(); ++i) {
					if (photonPlayerlist[i] != localPlayer.photonPlayer && cachedPlayerlist.contains(photonPlayerlist[i])) {
						if (cachedPlayerlist[photonPlayerlist[i]].loadingStage >= LoadingStage::LOADED) {

							const PlayerInfo& targetPlayer = cachedPlayerlist[photonPlayerlist[i]];

							if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
								playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

								const bool& internalDespawnToggle = globals::instantiateAssets::despawnToggle;
								Il2CppString* internalPrefab = il2cpp_string_new_spoof(globals::instantiateAssets::prefab.c_str());
								Vector3 internalScale = globals::instantiateAssets::scale;
								const Vector3 position = playerPlayer->get_CurrentBodyPosition();
								const Quaternion rotation = playerPlayer->GetRotation();

								if (globals::instantiateAssets::randomScaleToggle) {
									internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
									internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
									internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
								}

								for (int j = 0; j < globals::instantiateAssets::Count; j++) {
									PhotonNetwork::photonInstantiate(internalPrefab, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
								}
								PhotonNetwork::photonInstantiate(internalPrefab, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
							}
						}
					}
				}
			}
		}
		else {
			Log::error("playerlistMutex timed out in SpawnAssetAll!");
			return false;
		}

		return true;
	}

	bool SpawnAsset(Il2CppString* prefabName, const Vector3 position, const Quaternion rotation) {
		
		Vector3 internalScale = globals::instantiateAssets::scale;
		const bool& internalDespawnToggle = globals::instantiateAssets::despawnToggle;
		if (globals::instantiateAssets::randomScaleToggle) {
			internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
			internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
			internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
		}

		for (int j = 0; j < globals::instantiateAssets::Count; j++) {
			PhotonNetwork::photonInstantiate(prefabName, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
		}
		
		PhotonNetwork::photonInstantiate(prefabName, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
		return true;
	}

	bool SpawnAssetOnTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED && cachedPlayerlist.contains(targetPP))
		{
			if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
				targetPlayer.loadingStage >= LoadingStage::LOADED)
			{
				if (auto* targetPlayerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
					targetPlayerPlayer->get_IsInitialized() && targetPlayerPlayer->get_IsInitialLoadFinished())
				{
					const bool& internalDespawnToggle = globals::instantiateAssets::despawnToggle;
					Il2CppString* internalPrefab = il2cpp_string_new_spoof(globals::instantiateAssets::prefab.c_str());
					const Vector3 position = targetPlayerPlayer->get_CurrentBodyPosition();
					const Quaternion rotation = targetPlayerPlayer->GetRotation();
					
					Vector3 internalScale = globals::instantiateAssets::scale;
		
					if (globals::instantiateAssets::randomScaleToggle) {
						internalScale.x = getRandomScale(globals::instantiateAssets::randomScaleX);
						internalScale.y = getRandomScale(globals::instantiateAssets::randomScaleY);
						internalScale.z = getRandomScale(globals::instantiateAssets::randomScaleZ);
					}

					for (int j = 0; j < globals::instantiateAssets::Count; j++) {
						PhotonNetwork::photonInstantiate(internalPrefab, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
					}
					
					PhotonNetwork::photonInstantiate(internalPrefab, position, rotation, internalScale, 0, nullptr, internalDespawnToggle);
				}
			}
		}
		return true;
	}

	bool SpawnItemOnTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED && cachedPlayerlist.contains(targetPP))
		{
			if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
				if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
					Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
				return false;
			}
			
			if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
				targetPlayer.loadingStage >= LoadingStage::LOADED)
			{
				if (auto* targetPlayerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
					targetPlayerPlayer->get_IsInitialized() && targetPlayerPlayer->get_IsInitialLoadFinished())
				{
					Il2CppString* internalPrefab = il2cpp_string_new_spoof(globals::instantiate::prefab.c_str());
					const Vector3 position = targetPlayerPlayer->get_CurrentBodyPosition();
					const Quaternion rotation = targetPlayerPlayer->GetRotation();
					
					Vector3 internalScale = globals::instantiate::scale;
		
					if (globals::instantiate::randomScaleToggle) {
						internalScale.x = getRandomScale(globals::instantiate::randomScaleX);
						internalScale.y = getRandomScale(globals::instantiate::randomScaleY);
						internalScale.z = getRandomScale(globals::instantiate::randomScaleZ);
					}

					for (int j = 0; j < globals::instantiateAssets::Count; j++) {
						PhotonNetwork::photonInstantiateMC(internalPrefab, position, rotation, internalScale, 0, nullptr);
					}
					
					PhotonNetwork::photonInstantiateMC(internalPrefab, position, rotation, internalScale, 0, nullptr);
				}
			}
		}
		return true;
	}
}