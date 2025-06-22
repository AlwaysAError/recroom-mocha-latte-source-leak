#pragma once

struct EventData : Il2CppObject {

	typedef Il2CppString* (*toStringEvent_t)(EventData* eventData);
	Il2CppString* ToString() {
		const auto func = (toStringEvent_t)(methods::ExitGamesClientPhoton::EventData::toStringEvent);
		return func(this);
	}

	typedef Il2CppObject* (*get_CustomData_t)(EventData* eventData);
	Il2CppObject* get_CustomData() {
		const auto func = (get_CustomData_t)(methods::ExitGamesClientPhoton::EventData::getCustomDataEvent);
		return func(this);
	}

	typedef int32_t (*get_Sender_t)(EventData* eventData);
	int32_t get_Sender() {
		const auto func = (get_Sender_t)(methods::ExitGamesClientPhoton::EventData::getSenderEvent);
		return func(this);
	}

};