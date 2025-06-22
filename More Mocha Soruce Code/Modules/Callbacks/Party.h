#pragma once

namespace Callbacks
{

	bool JoinMyPartyTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr) {

			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
					targetPlayer.loadingStage >= LoadingStage::LOADED) {

					if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID)) {
						if (auto* party = GetField<PlayerParty*>(playerPlayer, 400)) {
							party->RpcJoinParty(localPlayer.photonPlayer, Vector3{ 0, -1000, 0 }, PlayerParty::PartyJoinedSource::RemoteCommand);
						}
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in JoinMyPartyTarget!");
				return false;
			}
		}
		
		return true;
	}

	bool JoinPartyTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr) {

			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}

				if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
					localPlayer.loadingStage >= LoadingStage::LOADED && targetPlayer.loadingStage >= LoadingStage::PHOTON) {

					if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID)) {
						if (auto* party = GetField<PlayerParty*>(playerPlayer, 400)) {
							party->RpcJoinParty(targetPlayer.photonPlayer, Vector3{ 0, -1000, 0 }, PlayerParty::PartyJoinedSource::Code);
						}
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in JoinPartyTarget!");
				return false;
			}
		}
		return true;
	}

	bool LeavePartyTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr) {

			std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (!cachedPlayerlist.contains(targetPP))
				{
					lock.unlock();
					return true;
				}
				
				if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
					targetPlayer.loadingStage >= LoadingStage::LOADED) {

					if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
						playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

						if (auto* party = GetField<PlayerParty*>(playerPlayer, 400)) {

							Il2CppString* partyId = party->get_CurrentPartyId();

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{(Il2CppObject*)partyId}
							};

							targetPlayer.photonView->SendRPC("RpcKickedFromParty", All, payloadVector);
						}
					}
				}

				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in LeavePartyTarget!");
				return false;
			}
		}
		
		return true;
	}
    
}