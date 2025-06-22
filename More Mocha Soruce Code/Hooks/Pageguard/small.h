#pragma once

enum AddFlyEnabledPriority
{
    DEFAULT = -2147483648,
    GAME_RULE_MANAGER = 500,
    GAME_ROLE_MANAGER = 10000,
    SOCCER_SPEED_POWERUP = 10001,
    SIT = 10001,
    SHARE_CAMERA = 10001,
    CUSTOM_LOCOMOTION = 100000,
    CREATOR_LOCOMOTION = 1000000,
    DEBUG = 2147483646,
    TEST = 2147483647,
};

typedef void(__fastcall *AddFlyEnabled_t)(void*, bool, Il2CppObject*, int, void* methodInfo);
void __fastcall AddFlyEnabled_hook(void* PlayerMovement, bool enabled, Il2CppObject* token, int priority, void* methodInfo) {

    const auto func = (AddFlyEnabled_t)(methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled);
	
    return veh::CallOriginal<void>(func, PlayerMovement, true, token, priority, methodInfo);
}

typedef int32_t(*GetNextGameplayRoomIndex_t)(void* instance, void* methodInfo);
int32_t __fastcall GetNextGameplayRoomIndex_hook(void* instance, void* methodInfo) {

	const auto func = (GetNextGameplayRoomIndex_t)(GameAssembly + 0x1004820); // obfuscated, one below GetCurrentGameplayRoomIndex()

	int32_t org = veh::CallOriginal<int32_t>(func, instance, methodInfo);
	int32_t totalRoomCount = GetField<int32_t>(instance, 336);

	// totally not copied from genesis
	if (org < totalRoomCount) {
		return totalRoomCount - 1;
	}

	return org;
}