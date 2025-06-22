#pragma once

struct NetworkPlayer;
struct RecRoomPlayer;

struct PhotonPlayer : Component {

	typedef Il2CppString* (*toStringUsername_t)(PhotonPlayer* photonPlayer);
	Il2CppString* toStringUsername() {
		const auto func = (toStringUsername_t)(methods::obfuscated::photon::PhotonPlayerToString);
		return func(this);
	}

	typedef Il2CppString* (*toStringAccountId_t)(PhotonPlayer* photonPlayer);
	Il2CppString* toStringAccountId() {
		const auto func = (toStringAccountId_t)(methods::obfuscated::photon::PhotonPlayerToStringFull);
		return func(this);
	}

	typedef int (*getActorNumber_t)(PhotonPlayer* photonPlayer);
	int getActorNumber() {
		return GetField<int>(this, 64);
	}

	Il2CppString* GetPlayerID()
	{
		return GetField<Il2CppString*>(this, 80);
	}
	
#ifndef CHEAP
	Hashtable* get_CustomProperties() {
		if (this == nullptr) return nullptr;
		return GetField<Hashtable*>(this, 96);
	}

	void set_CustomProperties(Hashtable* hashtable) {
		if (this == nullptr) return;
		return SetField<Hashtable*>(this, 96, hashtable);
	}
#endif

	NetworkPlayer* get_NetworkPlayer();
};