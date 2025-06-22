#pragma once

namespace Callbacks
{
	bool ExterminateTarget(PhotonPlayer* targetPP) {

		if (targetPP != nullptr)
		{
			std::unique_lock lock(playerlistMutex, std::defer_lock);

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::RECROOM)
				{
					if (!cachedPlayerlist.contains(targetPP))
					{
						lock.unlock();
						return false;
					}

					if (const PlayerInfo& targetPlayer = cachedPlayerlist[targetPP];
						targetPlayer.loadingStage >= LoadingStage::LOADED) {

						if (RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(targetPlayer.photonActorID);
							playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

							if (GameObject* gunObject = PhotonNetwork::photonInstantiate(WriteIl2CppString(globals::instantiateAssets::prefab.c_str()), {0, -1000, 0}, {0, 0, 0, 0}, {1, 1, 1}, 0, nullptr, true)) {
								if (Component* rangedWeaponComponent = gunObject->GetComponent("RecRoom.Core.Combat.RangedWeapon")) {
									if (auto* rangedWeaponMonoBehaviourPun = (MonoBehaviourPun*)rangedWeaponComponent) {
										if (PhotonView* photonView = rangedWeaponMonoBehaviourPun->get_PhotonView()) {

											Vector3 position = playerPlayer->get_Head()->get_transform()->get_position();
											position.y += 1.0f;

											Quaternion rotation = { 0.0f, 0.0f, 0.70711f, 0.70711f }; // straight down
											Vector3 velocity = { 0.0f, globals::exterminateVelocity, 0.0f };

											std::vector<PhotonView::PayloadEntry> payloadVector = {
												{position,			"UnityEngine.Vector3"},		// position
												{rotation,			"UnityEngine.Quaternion"},	// rotation
												{velocity,			"UnityEngine.Vector3"},		// velocity
												{1.0f,				"System.Single"},			// chargeAmount
												{false,				"System.Boolean"},			// misFire
												{(uint8_t)0,		"System.Byte"}				// shotId
											};

											photonView->SendRPC("RpcFireShot", All, payloadVector);
										}
									}
								}
							}
						}
					}
				}
				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in ExterminateTarget!");
				return false;
			}
		}

		return true;
	}
}