#pragma once

struct QuestManager : MonoBehaviourPun {

	typedef QuestManager* (*get_Instance_t)();
	static QuestManager* get_Instance() {
		const auto func = (get_Instance_t)(methods::QuestManager::get_Instance);
		return func();
	}

	typedef void (*set_DefaultRoomIndex_t)(QuestManager* instance, int32_t value);
	void set_DefaultRoomIndex(int32_t value) {
		const auto func = (set_DefaultRoomIndex_t)(methods::QuestManager::set_DefaultRoomIndex);
		return func(this, value);
	}

	typedef void (*TryGenerateLocalPlayerGift_t)(QuestManager* instance, int32_t value);
	void TryGenerateLocalPlayerGift(int32_t score) {
		const auto func = (TryGenerateLocalPlayerGift_t)(GameAssembly + 0x155F740); // obfuscated private, search term -> "METHOD(void, (QuestManager*, int32_t, MethodInfo*)"
		return func(this, score);
	}

	typedef void (*MasterAddPlayerPointsValue_t)(QuestManager* instance, NetworkPlayer* player, int32_t value);
	void MasterAddPlayerPointsValue(PhotonPlayer* player, int32_t deltaPoints) {
		if (player == nullptr) return;
		NetworkPlayer* networkPlayer = player->get_NetworkPlayer();
		if (networkPlayer == nullptr) return;
		const auto func = (MasterAddPlayerPointsValue_t)(GameAssembly + 0x15600F0); // obfuscated, search term -> "METHOD(void, (QuestManager*, PhotonPlayer*, int32_t, MethodInfo*)"
		return func(this, networkPlayer, deltaPoints);
	}

};