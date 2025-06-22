#pragma once

typedef int32_t(*get_Health_t)(void*, void*);
int32_t GetHealthHookLogic(void* instance, get_Health_t original, void* methodInfo) {

	if (globals::health::godmodeAll)
		return 2147483647;

	if (instance != nullptr) {

		if (auto* targetPP = GetField<PhotonPlayer*>(instance, 144); ((targetPP == localPlayer.photonPlayer) || (cachedPlayerlist[targetPP].hasGodmodeWhitelist)))
			return 2147483647;

		else if ((targetPP != nullptr)) {

			switch (globals::health::healthMode) {

			case globals::health::HealthMode::Static:
				return globals::health::staticValue;

			case globals::health::HealthMode::OneShot: {

				const int32_t originalHealth = original(instance, methodInfo);

				if (originalHealth > 0) // allow player to actually die lol
					return 1;

				return originalHealth;
			}

			default:
				return original(instance, methodInfo);

			}
		}
		return 1;
	}
	return 1;
}

get_Health_t get_Health_o = nullptr; // unused but required for trampoline
get_Health_t get_Health2_o = nullptr;
get_Health_t get_Health3_o = nullptr;
get_Health_t get_Health4_o = nullptr;
get_Health_t get_Health5_o = nullptr;
get_Health_t get_Health6_o = nullptr;

int32_t __fastcall get_Health_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health_o, methodInfo);
}

int32_t __fastcall get_Health2_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health2_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health2_o, methodInfo);
}

int32_t __fastcall get_Health3_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health3_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health3_o, methodInfo);
}

int32_t __fastcall get_Health4_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health4_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health4_o, methodInfo);
}

int32_t __fastcall get_Health5_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health5_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health5_o, methodInfo);
}

int32_t __fastcall get_Health6_Ihook(void* instance, void* methodInfo) {

	if (!globals::Ihooks::get_Health)
		return get_Health6_o(instance, methodInfo);

	return GetHealthHookLogic(instance, get_Health6_o, methodInfo);
}