#pragma once

namespace Callbacks
{
	bool TeleportToMeTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			/* apparently "Authority" doesn't mean shit
			if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
				if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
					Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
				return false;
			}
			*/
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				if (RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)) {
					Vector3 position = localPlayerPlayer->get_CurrentHeadPosition();

					std::vector<PhotonView::PayloadEntry> payloadVector = {
						{position, "UnityEngine.Vector3"}
					};

					targetPlayer.photonView->SendRPC("RpcAuthorityCV2SetPosition", All, payloadVector);
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in TeleportToMeTarget!");
				return false;
			}
		}
		return true;
	}

	bool TeleportToTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			/* apparently "Authority" doesn't mean shit
			if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
				if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
					Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
				return false;
			}
			*/
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				if (RecRoomPlayer* targetPlayerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID)) {

					Vector3 position = targetPlayerPlayer->get_CurrentBodyPosition();

					std::vector<PhotonView::PayloadEntry> payloadVector = {
						{position, "UnityEngine.Vector3"}
					};

					localPlayer.photonView->SendRPC("RpcAuthorityCV2SetPosition", localPlayer.photonPlayer, payloadVector);
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in TeleportToTarget!");
				return false;
			}
		}
		return true;
	}

	bool TeleportAllToTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED) {

			/* apparently "Authority" doesn't mean shit
			if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
				if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
					Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
				return false;
			}
			*/
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);
			
			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				if (RecRoomPlayer* targetPlayerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
					targetPlayerPlayer->get_IsInitialized() && targetPlayerPlayer->get_IsInitialLoadFinished()) {

					Vector3 position = targetPlayerPlayer->get_CurrentHeadPosition();

					std::vector<PhotonView::PayloadEntry> payloadVector = {
						{position, "UnityEngine.Vector3"}
					};

					for (int i = 0; i < photonPlayerlist.size(); ++i) {
						if (photonPlayerlist[i] != targetPP) {
							if (cachedPlayerlist[photonPlayerlist[i]].loadingStage >= LoadingStage::LOADED) { // ignore loading players entirely

								const PlayerInfo& targetPlayerInfo = cachedPlayerlist[photonPlayerlist[i]];

								targetPlayerInfo.photonView->SendRPC("RpcAuthorityCV2SetPosition", All, payloadVector);
							}
						}
					}
				}
				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in TeleportAllToTarget!");
				return false;
			}
		}

		return true;
	}

	bool TeleportToLimitTarget(PhotonPlayer* targetPP) { // this doesn't actually teleport them to infinity, just very far (RpcAuthorityCV2SetPosition is sanitized on the server...)

		if (targetPP != nullptr && localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			/* apparently "Authority" doesn't mean shit
			if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
				if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
					Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
				return false;
			}
			*/
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
				
				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];

				constexpr float maxx = 99999993215964691371151521984339247104.000f;
				constexpr float minn = -99999993215964691371151521984339247104.000f;
				Vector3 position = { maxx, maxx, minn }; // this vector3 gets sanitized in the RPC call

				std::vector<PhotonView::PayloadEntry> payloadVector = {
					{position, "UnityEngine.Vector3"} // position
				};
				
				targetPlayer.photonView->SendRPC("RpcAuthorityCV2SetPosition", All, payloadVector);

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in TeleportToLimitTarget!");
				return false;
			}
		}
		return true;
	}
}