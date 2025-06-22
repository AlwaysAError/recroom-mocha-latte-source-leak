#pragma once

namespace Callbacks {
	
	bool LeavePartyUnsafe(PhotonPlayer* targetPP) {

		if (targetPP != nullptr && cachedPlayerlist.contains(targetPP)) {

			if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
				targetPlayer.loadingStage >= LoadingStage::LOADED) {

				if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID)) {
					
					if (auto* party = GetField<PlayerParty*>(playerPlayer, 400)) {

						Il2CppString* partyId = party->get_CurrentPartyId();

						std::vector<PhotonView::PayloadEntry> payloadVector = {
							{(Il2CppObject*)partyId}
						};

						targetPlayer.photonView->SendRPC("RpcKickedFromParty", All, payloadVector);
					}
				}
			}
		}

		return true;
	}

	bool GoToRoomTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr) {

			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
				if (!cachedPlayerlist.contains(targetPP)) {
					lock.unlock();
					return true;
				}
				
				if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
					targetPlayer.loadingStage >= LoadingStage::LOADED)
				{
					std::vector<PhotonView::PayloadEntry> payloadVector = {
						{(Il2CppObject*)WriteIl2CppString(globals::roomNameBuffer.c_str())},	// roomName
						{(Il2CppObject*)WriteIl2CppString("")},							// subRoomName
						{(Il2CppObject*)WriteIl2CppString("")},							// welcomeMatName
						{RoomDoorInviteMode::EveryoneAutoFollow, "System.Int32"},		// inviteMode
						{true, "System.Boolean"},										// forceNewInstance 
					};

					if (globals::forceLeavePartyGas)
						LeavePartyUnsafe(targetPP);

					targetPlayer.photonView->SendRPC("RpcLocalGoToRoom", targetPP, payloadVector);
				}
				
				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in GoToRoomTarget!");
				return false;
			}
		}
		return true;
	}

	bool GoToRoomAll() {

		if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
			
				for (const auto& [photonPlayer, playerInfo] : cachedPlayerlist) {
					if (!playerInfo.isLocalPlayer && playerInfo.loadingStage >= LoadingStage::LOADED) {

						std::vector<PhotonView::PayloadEntry> payloadVector = {
							{(Il2CppObject*)WriteIl2CppString(globals::roomNameBuffer.c_str())},	// roomName
							{(Il2CppObject*)WriteIl2CppString("")},							// subRoomName
							{(Il2CppObject*)WriteIl2CppString("")},							// welcomeMatName
							{RoomDoorInviteMode::EveryoneAutoFollow, "System.Int32"},		// inviteMode
							{true, "System.Boolean"},										// forceNewInstance 
						};

						if (globals::forceLeavePartyGas)
							LeavePartyUnsafe(photonPlayer);
					
						playerInfo.photonView->SendRPC("RpcLocalGoToRoom", photonPlayer, payloadVector);
						playerInfo.photonView->SendRPC("RpcLocalGoToRoom", photonPlayer, payloadVector);
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in TeleportFarPL!");
				return false;
			}
		}

		return true;
	}
}