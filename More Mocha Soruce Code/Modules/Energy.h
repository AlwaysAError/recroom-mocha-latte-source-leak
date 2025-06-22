#pragma once

Il2CppType* cachedObjectType;

#ifdef ENERGY
std::string pos = "0, 0, 0";

void EnergyList() {
	ImGui::Begin("Energy Modules", nullptr);

	if (ImGui::Button("Get Position"))
	{
		std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

		if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

			Transform* cuntFuckTransform = localPlayer.playerGameObject->get_transform();
			Transform* localChildBodyPartsTransform = cuntFuckTransform->GetChild(0);
			Transform* localHeadTransform = localChildBodyPartsTransform->GetChild(0);

			Vector3 newPos = localHeadTransform->get_position();
			pos = std::to_string(newPos.x) + ", " + std::to_string(newPos.y) + ", " + std::to_string(newPos.z);

			lock.unlock();
		}
		else {
			Log::error("playerlistMutex timed out in Get Position Button!");
		}
	}
	ImGui::SameLine();
	ImGui::Text(pos.c_str());

	ImGui::End();
}

Vector3 posToMoveTo = { 118.111, 53.129, -24.601 };

void TowerGameDrop(PhotonPlayer* pPlayer)
{
	PlayerInfo& targetPlayer = cachedPlayerlist[pPlayer];

	while (globals::energy::towerModuleToggle)
	{
		bool found = false;
		for (const auto& [photonPlayer, player] : cachedPlayerlist) {
			if (targetPlayer.photonPlayer == photonPlayer) {
				found = true;
				break;
			}
		}

		if (found)
		{
			Transform* cuntFuckTransform = targetPlayer.playerGameObject->get_transform();
			Transform* localChildBodyPartsTransform = cuntFuckTransform->GetChild(0);
			Transform* localHeadTransform = localChildBodyPartsTransform->GetChild(0);
			Vector3 posCheck = localHeadTransform->get_position();

			if ((posCheck.x > 122.573 or posCheck.x < 112.219) or (posCheck.y > 55.549 or posCheck.y < 52.124) or (posCheck.z > -19.943 or posCheck.z < -29.385))
			{
				//Log::debug("Not in perimeter");
				Il2CppString* RPCEvent = il2cpp_string_new_spoof("RpcAuthorityCV2SetPosition");
				Il2CppArray* payloadArray = Array::createInstance(cachedObjectType, 1);
				Il2CppObject* positionObject = il2cpp_value_box_spoof(FindClass("UnityEngine.Vector3"), &posToMoveTo); // use cached findClass("UnityEngine.Vector3") cuz it's const*
				il2cpp_array_set(payloadArray, Il2CppObject*, 0, positionObject);
				Il2CppObject* RPCPayload = reinterpret_cast<Il2CppObject*>(payloadArray);
				if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
					if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer))
						Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
					Sleep(250);
				}
				PhotonView* photonCuntView = static_cast<PhotonView*>(targetPlayer.playerGameObject->GetComponent("PhotonView"));
				photonCuntView->RPC(RPCEvent, All, RPCPayload);
			}
		}
		else
		{
			Log::debug("Turn off player has left.");
		}

		Sleep(1000);
	}
}
#endif