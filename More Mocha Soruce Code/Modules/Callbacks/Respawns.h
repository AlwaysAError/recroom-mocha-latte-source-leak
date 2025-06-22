#pragma once

namespace Callbacks
{
	bool RespawnPlayerTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				if (auto* targetPlayerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
					targetPlayerPlayer->get_IsInitialized() && targetPlayerPlayer->get_IsInitialLoadFinished())
				{
					if (auto* RecRoomSceneManager = RecRoomSceneManager::get_Instance()) {
						if (auto* photonView = RecRoomSceneManager->get_PhotonView()) {

							Vector3 position = targetPlayerPlayer->get_CurrentHeadPosition();
							Quaternion rotation = targetPlayerPlayer->GetRotation();

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{position, "UnityEngine.Vector3"},			// spawnPosition
								{rotation, "UnityEngine.Quaternion"},		// spawnRotation
								{(Il2CppObject*)targetPlayer.photonView},	// spawnParent
								{true, "System.Boolean"}					// dropTools
							};
							
							photonView->SendRPC("RpcRespawnPlayer", targetPP, payloadVector);
						}
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in RespawnPlayerTarget!");
				return false;
			}
		}

		return true;
	}

	bool DespawnPlayerTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
				
				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				std::vector<PhotonView::PayloadEntry> payloadVector = {
					{true, "System.Boolean"} // suppressAnimation
				};

				targetPlayer.photonView->SendRPC("RpcBroadcastDespawnPlayer", All, payloadVector);

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in DespawnPlayerTarget!");
				return false;
			}
		}
		return true;
	}

	bool SpawnPlayerTarget(PhotonPlayer* targetPP) {
		
		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
			
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				std::vector<PhotonView::PayloadEntry> payloadVector = {
					{false, "System.Boolean"},					// firstSpawn
					{Vector3{0, 0, 0}, "UnityEngine.Vector3"},	// spawnPosition
					{false, "System.Boolean"}					// suppressAnimation
				};
				
				targetPlayer.photonView->SendRPC("RpcBroadcastSpawnPlayer", All, payloadVector);

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in SpawnPlayerTarget");
				return false;
			}
		}

		return true;
	}

	bool RespawnAtInfinityTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				if (RecRoomSceneManager* RecRoomSceneManager = RecRoomSceneManager::get_Instance()) {
					if (PhotonView* photonView = RecRoomSceneManager->get_PhotonView()) {

						constexpr float maxx = 99999993215964691371151521984339247104.000f;
						constexpr float minn = -99999993215964691371151521984339247104.000f;

						Vector3 position = { maxx, maxx, minn };

						std::vector<PhotonView::PayloadEntry> payloadVector = {
							{position, "UnityEngine.Vector3"},					// spawnPosition
							{Quaternion{0, 0, 0, 0}, "UnityEngine.Quaternion"}, // spawnRotation
							{(Il2CppObject*)targetPlayer.photonView},			// spawnParent
							{true, "System.Boolean"}							// dropTools
						};
						
						photonView->SendRPC("RpcRespawnPlayer", targetPP, payloadVector);
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in RespawnAtInfinityTarget!");
				return false;
			}
		}
		return true;
	}
}