#pragma once

struct UList
{
	typedef int32_t (*get_Count_t)(UList* instance);
	int32_t get_Count() {
		const auto func = (get_Count_t)(GameAssembly + 0x0);
		return func(this);
	}

	typedef Il2CppObject* (*get_Item_t)(UList* instance, int index);
	Il2CppObject* get_Item(int index) {
		const auto func = (get_Item_t)(GameAssembly + 0x0);
		return func(this, index);
	}
};

struct RoomName
{
	typedef Il2CppString* (*get_RoomName_t)(RoomName* instance);
	Il2CppString* get_RoomName() {
		const auto func = (get_RoomName_t)(GameAssembly + 0x0);
		return func(this);
	}
};

struct Rooms;

struct DissonanceComms
{
	typedef Rooms* (*get_Rooms_t)(DissonanceComms* instance);
	Rooms* get_Rooms() {
		const auto func = (get_Rooms_t)(GameAssembly + 0x0);
		return func(this);
	}
};