#pragma once

struct Hashtable : UObject {

	typedef void (*StaticConstructor_t)(Hashtable* hashtable);
	static Hashtable* ctor()
	{
		const Il2CppClass* klass = FindClass("ExitGames.Client.Photon.Hashtable");
		auto* object = (Hashtable*)il2cpp_object_new_spoof(klass);
		if (object == nullptr)
			return nullptr;
		const auto func = (StaticConstructor_t)(methods::ExitGamesClientPhoton::Hashtable::StaticConstructor);
		func(object);
		return object;
	}

	typedef void (*Add_t)(Hashtable* hashtable, BYTE byte, UObject* object);
	void Add(BYTE byte, UObject* object)
	{
		if (this == nullptr) return;
		const auto func = (Add_t)(methods::ExitGamesClientPhoton::Hashtable::Add);
		func(this, byte, object);
	}

	typedef Il2CppString* (*ToString_t)(Hashtable* hashTable);
	Il2CppString* ToString() {
		const auto func = (ToString_t)(methods::ExitGamesClientPhoton::Hashtable::ToString);
		return func(this);
	}

	typedef Il2CppObject* (*getItem_t)(Hashtable* hashtable, uint8_t key);
	Il2CppObject* get_Item(uint8_t key) {
		const auto func = (getItem_t)(methods::ExitGamesClientPhoton::Hashtable::get_Item);
		return func(this, key);
	}

	typedef Il2CppObject* (*getItem2_t)(Hashtable* hashtable, Il2CppObject* key);
	Il2CppObject* get_Item2(Il2CppObject* key) {
		const auto func = (getItem2_t)(methods::ExitGamesClientPhoton::Hashtable::get_Item2);
		return func(this, key);
	}

	typedef void (*set_Item_t)(Hashtable* hashtable, BYTE byte, UObject* object);
	void set_Item(BYTE key, UObject* value) {
		const auto func = (set_Item_t)(methods::ExitGamesClientPhoton::Hashtable::set_Item);
		return func(this, key, value);
	}

	typedef void (*setItem2_t)(Hashtable* hashtable, Il2CppObject* key, Il2CppObject* value);
	void set_Item2(Il2CppObject* key, Il2CppObject* value) {
		const auto func = (setItem2_t)(methods::ExitGamesClientPhoton::Hashtable::set_Item2);
		return func(this, key, value);
	}

};