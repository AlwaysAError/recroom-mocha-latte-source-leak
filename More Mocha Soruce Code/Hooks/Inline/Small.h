#pragma once

typedef bool (*get_IsFlyingEnabled_t)(void*, void*);
get_IsFlyingEnabled_t get_IsFlyingEnabled_o = nullptr;
bool __fastcall get_IsFlyingEnabled_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_IsFlyingEnabled)
		return get_IsFlyingEnabled_o(instance, methodInfo);

	return true;
}

typedef void (*set_FieldOfView_t)(void*, float, void*);
set_FieldOfView_t set_FieldOfView_o = nullptr;
void __fastcall set_FieldOfView_Ihook(void* camera, float value, void* methodInfo) {

	if (!globals::Ihooks::set_FieldOfView)
		return hook_manager::get()["fov"]->call<void>(camera, value, methodInfo);
		//return set_FieldOfView_o(camera, value, methodInfo);

	const float& internalFOV = globals::fov::fov;
	const float& internalZoomFOV = globals::fov::zoomFov;
	const bool& internalZoomToggle = globals::fov::zoomToggle;
	const bool& internalZoomState = globals::fov::zoomState;

	return internalZoomToggle && internalZoomState ?
		hook_manager::get()["fov"]->call<void>(camera, internalZoomFOV, methodInfo) :
		hook_manager::get()["fov"]->call<void>(camera, internalFOV, methodInfo);
	
	/*
	return internalZoomToggle && internalZoomState ?
		set_FieldOfView_o(camera, internalZoomFOV, methodInfo) :
		set_FieldOfView_o(camera, internalFOV, methodInfo);
		*/
}

typedef void(*AddFlyEnabled_t)(void*, bool, Il2CppObject*, int, void*);
AddFlyEnabled_t AddFlyEnabled_o = nullptr;
void __fastcall AddFlyEnabled_Ihook(void* PlayerMovement, bool enabled, Il2CppObject* token, int priority, void* methodInfo) {

	if (!globals::Ihooks::AddFlyEnabled)
		return AddFlyEnabled_o(PlayerMovement, enabled, token, priority, methodInfo);

	return AddFlyEnabled_o(PlayerMovement, true, token, priority, methodInfo);
}

typedef int32_t(*GetNextGameplayRoomIndex_t)(void*, void*);
GetNextGameplayRoomIndex_t GetNextGameplayRoomIndex_o = nullptr;
int32_t __fastcall GetNextGameplayRoomIndex_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::AddFlyEnabled)
		return GetNextGameplayRoomIndex_o(instance, methodInfo);

	const int32_t original = GetNextGameplayRoomIndex_o(instance, methodInfo);
	
	if (const int32_t totalRoomCount = GetField<int32_t>(instance, 336);
		original < totalRoomCount) { // totally not copied from genesis, thanks TheOneAboveAll & 567
		return totalRoomCount - 1;
	}

	return original;
}

typedef void (*RequestDropBeacon_t)(void*, Vector3, int, void*);
RequestDropBeacon_t RequestDropBeacon_o = nullptr;
void __fastcall RequestDropBeacon_Ihook(void* instance, Vector3 position, int type, void* methodInfo) {

	if (!globals::Ihooks::RequestDropBeacon)
		return RequestDropBeacon_o(instance, position, type, methodInfo);

	return;
}

typedef void (*RpcPlaySample_t)(void* instance, Il2CppString* blobName, float audioLength, Il2CppString* audioName, void* methodInfo);
RpcPlaySample_t RpcPlaySample_o = nullptr;
void __fastcall RpcPlaySample_Ihook(void* instance, Il2CppString* blobName, float audioLength, Il2CppString* audioName, void* methodInfo) {
	
	const auto func = (RpcPlaySample_t)reinterpret_cast<void*>(RpcPlaySample_o);
	
	if (!globals::Ihooks::RpcPlaySample)
		return veh::CallOriginal<void>(func, instance, blobName, audioLength, audioName, methodInfo);
		//return hook_manager::get()["play"]->call<void>(instance, blobName, audioLength, audioName, methodInfo);
		//return RpcPlaySample_o(instance, blobName, audioLength, audioName, methodInfo);

	if (instance != nullptr) {
		Log::debug("================================");
		Log::debug("blobName: " + std::string(ReadIl2CppString(blobName)));
		Log::debug("audioLength: " + std::to_string(audioLength));
		Log::debug("audioName: " + std::string(ReadIl2CppString(audioName)));
		Log::debug("================================");
	}

	return veh::CallOriginal<void>(func, instance, blobName, audioLength, audioName, methodInfo);
	//return hook_manager::get()["play"]->call<void>(instance, blobName, audioLength, audioName, methodInfo);
	//return RpcPlaySample_o(instance, blobName, audioLength, audioName, methodInfo);
}

typedef void* (*RpcLocalGoToRoom_t)(void*, Il2CppString*, Il2CppString*, Il2CppString*, int32_t, bool, void*);
RpcLocalGoToRoom_t RpcLocalGoToRoom_o = nullptr;
void* __fastcall RpcLocalGoToRoom_Ihook(void* instance, Il2CppString* idk1, Il2CppString* idk2, Il2CppString* idk3, int32_t idk4, bool idk5, void* methodInfo) {

	if (!globals::Ihooks::RpcLocalGoToRoom)
		return RpcLocalGoToRoom_o(instance, idk1, idk2, idk3, idk4, idk5, methodInfo);

	Log::debug("RpcLocalGoToRoom called!");

	return nullptr;
}

enum class InventionPermission
{
	Unassigned = 0,
	LimitedOneUseOnly = 10,
	DisallowKeyLock = 15,
	UseOnly = 20,
	EditAndSave = 40,
	Publish = 60,
	Charge = 80,
	Unlimited = 100,
};

typedef InventionPermission (*get_InventionPermission_t)(void*, void*);
get_InventionPermission_t get_InventionPermission_o = nullptr;
InventionPermission __fastcall get_InventionPermission_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::CreationObjectInventions)
		return get_InventionPermission_o(instance, methodInfo);

	return InventionPermission::Unlimited;
}

typedef bool (*get_CanSaveIntoInventions_t)(void*, void*);
get_CanSaveIntoInventions_t get_CanSaveIntoInventions_o = nullptr;
bool __fastcall get_CanSaveIntoInventions_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::CreationObjectInventions)
		return get_CanSaveIntoInventions_o(instance, methodInfo);

	return true;
}

typedef bool (*get_CanPublishInInventions_t)(void*, void*);
get_CanPublishInInventions_t get_CanPublishInInventions_o = nullptr;
bool __fastcall get_CanPublishInInventions_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::CreationObjectInventions)
		return get_CanPublishInInventions_o(instance, methodInfo);

	return true;
}

typedef bool (*get_IsOnCooldown_t)(void*, void*);
get_IsOnCooldown_t get_IsOnCooldown_o = nullptr;
bool __fastcall get_IsOnCooldown_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_IsOnCooldown)
		return get_IsOnCooldown_o(instance, methodInfo);

	return false;
}

typedef bool (*DoesLocalPlayerOwnKey1_t)(void*, void*, void*);
DoesLocalPlayerOwnKey1_t DoesLocalPlayerOwnKey1_o = nullptr;
bool __fastcall DoesLocalPlayerOwnKey1_Ihook(void* instance, void* replicationId, void* methodInfo) {

	if (!globals::Ihooks::DoesLocalPlayerOwnKey)
		return DoesLocalPlayerOwnKey1_o(instance, replicationId, methodInfo);

	return true;
}

typedef bool (*DoesLocalPlayerOwnKey2_t)(void*, int64_t, void*);
DoesLocalPlayerOwnKey2_t DoesLocalPlayerOwnKey2_o = nullptr;
bool __fastcall DoesLocalPlayerOwnKey2_Ihook(void* instance, int64_t roomKeyId, void* methodInfo) {

	if (!globals::Ihooks::DoesLocalPlayerOwnKey)
		return DoesLocalPlayerOwnKey2_o(instance, roomKeyId, methodInfo);

	return true;
}

typedef bool (*get_IsDeveloper_t)(void*);
get_IsDeveloper_t get_IsDeveloper_o = nullptr;
bool __fastcall get_IsDeveloper_Ihook(void* methodInfo) {

	if (!globals::Ihooks::get_IsDeveloper)
		return get_IsDeveloper_o(methodInfo);

	return true;
}

typedef bool (*get_HasActiveRRPlusSubscription_t)(void*);
get_HasActiveRRPlusSubscription_t get_HasActiveRRPlusSubscription_o = nullptr;
bool __fastcall get_HasActiveRRPlusSubscription_Ihook(void* methodInfo) {

	if (!globals::Ihooks::get_HasActiveRRPlusSubscription)
		return get_HasActiveRRPlusSubscription_o(methodInfo);

	return true;
}

typedef bool (*get_LocalAccountIsDeveloper_t)(void*, void*);
get_LocalAccountIsDeveloper_t get_LocalAccountIsDeveloper_o = nullptr;
bool __fastcall get_LocalAccountIsDeveloper_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_IsDeveloper)
		return get_LocalAccountIsDeveloper_o(instance, methodInfo);

	return true;
}

typedef bool (*get_LocalAccountIsModerator_t)(void*, void*);
get_LocalAccountIsModerator_t get_LocalAccountIsModerator_o = nullptr;
bool __fastcall get_LocalAccountIsModerator_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_LocalAccountIsModerator)
		return get_LocalAccountIsModerator_o(instance, methodInfo);

	return true;
}

/// ToxMod

typedef bool (*CanInitializeToxMod_t)(void*);
CanInitializeToxMod_t CanInitializeToxMod_o = nullptr;
bool __fastcall CanInitializeToxMod_Ihook(void* methodInfo) {

	if (!globals::Ihooks::DisableToxMod)
		return CanInitializeToxMod_o(methodInfo);

	return false;
}

typedef void (*PhotonVoiceCreated_t)(void*, void*, void*);
PhotonVoiceCreated_t PhotonVoiceCreated_o = nullptr;
void __fastcall PhotonVoiceCreated_Ihook(void* instance, void* params, void* methodInfo) {

	if (!globals::Ihooks::DisableToxMod)
		return PhotonVoiceCreated_o(instance, params, methodInfo);

	return;
}

typedef void (*Start_t)(void*, void*);
Start_t Start_o = nullptr;
void __fastcall Start_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::DisableToxMod)
		return Start_o(instance, methodInfo);

	return;
}

typedef void (*OnFloatAudioFrame_t)(void*, void*, void*);
OnFloatAudioFrame_t OnFloatAudioFrame_o = nullptr;
void __fastcall OnFloatAudioFrame_Ihook(void* instance, void* strukt, void* methodInfo) {

	if (!globals::Ihooks::DisableToxMod)
		return OnFloatAudioFrame_o(instance, strukt, methodInfo);

	return;
}

