#pragma once

enum class DestroyFlags
{
	None = 0,
	DisembodyOnly = 1,
	DestroyImmediately = 2,
};

namespace PhotonNetwork {

	typedef bool (*get_isMasterClient_t)(PhotonPlayer* photonPlayer);
	bool get_isMasterClient(PhotonPlayer* photonPlayer) {
		const auto func = (get_isMasterClient_t)(methods::obfuscated::photon::get_isMasterClient);
		return func(photonPlayer);
	}

	typedef bool (*setMasterClient_t)(NetworkPlayer* photonPlayer, void* methodInfo);
	bool set_MasterClient(PhotonPlayer* photonPlayer) {
		if (photonPlayer == nullptr) return false;
		NetworkPlayer* networkPlayer = photonPlayer->get_NetworkPlayer();
		if (networkPlayer == nullptr) return false;
		const auto func = (setMasterClient_t)(methods::obfuscated::photon::setMasterClient);
		return func(networkPlayer, nullptr);
	}

	typedef void (*Destroy1_t)(PhotonView* photonView);
	void Destroy1(PhotonView* photonView) {
		const auto func = (Destroy1_t)(methods::obfuscated::photon::Destroy1);
		return func(photonView);
	}

	typedef void (*Destroy2_t)(PhotonView* photonView);
	void Destroy2(PhotonView* photonView) {
		const auto func = (Destroy2_t)(methods::obfuscated::photon::Destroy2);
		return func(photonView);
	}

	typedef void (*Destroy3_t)(PhotonView* photonView);
	void Destroy3(PhotonView* photonView) {
		const auto func = (Destroy3_t)(methods::obfuscated::photon::Destroy3);
		return func(photonView);
	}

	typedef void (*Destroy4_t)(PhotonView* photonView);
	void Destroy4(PhotonView* photonView) {
		const auto func = (Destroy4_t)(methods::obfuscated::photon::Destroy4);
		return func(photonView);
	}

	typedef void (*Destroy5_t)(PhotonView* photonView);
	void Destroy5(PhotonView* photonView) {
		const auto func = (Destroy5_t)(methods::obfuscated::photon::Destroy5);
		return func(photonView);
	}

	typedef void (*Destroy6_t)(PhotonView* photonView);
	void Destroy6(PhotonView* photonView) {
		const auto func = (Destroy6_t)(methods::obfuscated::photon::Destroy6);
		return func(photonView);
	}

	typedef GameObject* (*photonInstantiate_t)(Il2CppString* prefabName, Vector3 position, Quaternion rotation, float scale, uint8_t group, void* arrayList, bool despawnable, bool idk);
	GameObject* photonInstantiate(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, void* arrayList, bool despawnable, bool idk = false) {
		const auto func = (photonInstantiate_t)(methods::obfuscated::photon::photonInstantiateAssets);

		GameObject* gameObject = spoof_call(returnSpoofAddress, func, prefabName, position, rotation, 1.0f, group, arrayList, despawnable, idk);

		if (gameObject != nullptr)
		{
			gameObject->get_transform()->set_localScale(scale);
		}

		return gameObject;
	}

	typedef GameObject* (*photonInstantiateMC_t)(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, void* arrayList);
	GameObject* photonInstantiateMC(Il2CppString* prefabName, Vector3 position, Quaternion rotation, Vector3 scale, uint8_t group, void* arrayList) {
		const auto func = (photonInstantiateMC_t)(methods::obfuscated::photon::photonInstantiate);
		return spoof_call(returnSpoofAddress, func, prefabName, position, rotation, scale, group, arrayList);
	}

	typedef Il2CppArray* (*photonPlayerOthersList_t)();
	Il2CppArray* photonPlayerOthersList() {
		const auto func = (photonPlayerOthersList_t)(methods::obfuscated::photon::photonPlayerOthersList);
		return func();
	}

	typedef Il2CppArray* (*photonPlayerList_t)();
	Il2CppArray* get_photonPlayerList() {
		const auto func = (photonPlayerList_t)(methods::obfuscated::photon::photonPlayerList);
		return func();
	}

	typedef bool (*OpRaiseEvent_t)(Il2CppObject* client, BYTE eventCode, Il2CppObject* customEventContent, Il2CppObject* raiseEventOptions, Il2CppObject* sendOptions);
	bool OpRaiseEvent(Il2CppObject* client, BYTE eventCode, Il2CppObject* customEventContent, Il2CppObject* raiseEventOptions, Il2CppObject* sendOptions) {
		const auto func = (OpRaiseEvent_t)(methods::obfuscated::photon::OpRaiseEvent);
		return func(client, eventCode, customEventContent, raiseEventOptions, sendOptions);
	}

	typedef void (*OnEvent_t)(EventData* eventData, void* methodInfo);
	static void OnEvent(EventData* eventData) {
		const auto func = (OnEvent_t)(methods::obfuscated::photon::OnEvent); // search term (in PhotonNetwork class) -> "METHOD(void, (UnityEngine::GameObject*, bool, "
		return func(eventData, nullptr);
	}

	typedef int32_t(*AllocateViewID_t)(int32_t ownerId, bool destroyOnLeave);
	static int32_t AllocateViewID(int32_t ownerId, bool destroyOnLeave) {
		const auto func = (AllocateViewID_t)(GameAssembly + 0x7DB18A0); // search term (in PhotonNetwork class) -> "METHOD(int32_t, (int32_t, bool, MethodInfo*)"
		return func(ownerId, destroyOnLeave);
	}

}