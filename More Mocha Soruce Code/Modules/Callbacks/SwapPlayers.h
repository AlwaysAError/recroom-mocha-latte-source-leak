#pragma once

namespace Callbacks
{
	bool RotateAllPL() {

		if (cachedPlayerlist.size() < 2) {
			return true;
		}

		if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			for (int i = 0; i < cachedPlayerlist.size(); ++i) {

				const PlayerInfo& currentPlayer = cachedPlayerlist[photonPlayerlist[i]];

				if ((currentPlayer.loadingStage <= LoadingStage::PHOTON) || currentPlayer.isLocalPlayer) {
					continue;
				}

				int nextIndex = (i + 1) % cachedPlayerlist.size();
				PlayerInfo nextPlayer = cachedPlayerlist[photonPlayerlist[nextIndex]];

				if (nextPlayer.loadingStage <= LoadingStage::PHOTON) {
					continue;
				}

				if (nextPlayer.isLocalPlayer) {
					nextIndex = (i + 2) % cachedPlayerlist.size();
					nextPlayer = cachedPlayerlist[photonPlayerlist[nextIndex]];
				}

				const RecRoomPlayer* currentPlayerPlayer = RecRoomPlayer::GetFromActorNumber(currentPlayer.photonActorID);

				if (RecRoomPlayer* nextPlayerPlayer = RecRoomPlayer::GetFromActorNumber(nextPlayer.photonActorID);
					(currentPlayerPlayer != nullptr) && (nextPlayerPlayer != nullptr)) {

					//Log::debug("Iter TP : " + std::string(currentPlayer.DisplayName) + " -> " + std::string(nextPlayer.DisplayName));

					Vector3 position = nextPlayerPlayer->get_TrackingSpace()->get_transform()->get_position();
					Quaternion rotation = nextPlayerPlayer->get_Head()->get_transform()->get_rotation();

					std::vector<PhotonView::PayloadEntry> payloadVector = {
						{position, "UnityEngine.Vector3"},			// spawnPosition
						{rotation, "UnityEngine.Quaternion"},		// spawnRotation
						{(Il2CppObject*)currentPlayer.photonView},	// spawnParent
						{false, "System.Boolean"}					// dropTools
					};

					
					if (auto* RecRoomSceneManager = RecRoomSceneManager::get_Instance()) {
						if (PhotonView* photonView = RecRoomSceneManager->get_PhotonView()) {
							photonView->SendRPC("RpcRespawnPlayer", currentPlayer.photonPlayer, payloadVector);
						}
					}
				}
			}
		}

		return true;
	}
}