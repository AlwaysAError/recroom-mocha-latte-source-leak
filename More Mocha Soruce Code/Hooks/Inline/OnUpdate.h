#pragma once
#include "Dependencies/HWBP/hwbp.hpp"
std::chrono::steady_clock::time_point lastExecutionTime250OU = std::chrono::steady_clock::now();
constexpr std::chrono::milliseconds threshold250OU(1);

void ForceMasterClient();
void ShaderChamsLogic();
void CircuitsDisablerLogic();
void SitOnHeadLoop();
void MakerPenDropperLoop();

struct OnUpdateParamInfo
{
	void* instance;
	void* methodInfo;
};

void __fastcall SafeCall_OnUpdate_o(void* params);

typedef void(*OnUpdate_t)(void*, void*);
OnUpdate_t OnUpdate_o = nullptr;
void OnUpdate_Ihook(void* instance, void* methodInfo) {

	//Log::debug("OnUpdate_Ihook");
	
	/*
	
	OnUpdateParamInfo params{
		instance,
		methodInfo
	};

	OnUpdateParamInfo* pParams = &params;
	return CallWithExceptionHandling(SafeCall_OnUpdate_o, pParams);
	*/
	Log::debug("test1");
	if (!globals::Ihooks::OnUpdate)
		return hook_manager::get()["Sleep"]->call<void>(instance, methodInfo);
		//return OnUpdate_o(instance, methodInfo);
	Log::debug("test2");
	//Log::debug("OnUpdate_Ihook");
	
	if (const auto& updatePlayerlist = globals::updatePlayerlistOnUpdate;
		updatePlayerlist)
	{
		const auto currentTime = std::chrono::steady_clock::now();

		if (const auto elapsedTime250 = currentTime - lastExecutionTime250OU;
			elapsedTime250 > threshold250OU)
		{ // only every 250ms
			Log::debug("testwigger1");
			PlayerlistUpdate();
			Log::debug("testwigger2");
			ForceMasterClient();
			Log::debug("testwigger3");
			ShaderChamsLogic();
			Log::debug("testwigger4");
			CircuitsDisablerLogic();
			Log::debug("testwigger5");
			MakerPenDropperLoop();
			Log::debug("testwigger6");
			lastExecutionTime250OU = currentTime;
		}
	}
	Log::debug("test3");
	if (globals::watchMenuTest) // hook priority check not needed here since this is an Ihook
		pWatchMenuHandler->Update();
	Log::debug("test4");
	//if (globals::onUpdate::inExecution)
	OnUpdateQueueLogic();
	Log::debug("test5");
	const auto& internalRapidFireToggle = globals::rapidFireToggle;
	const auto& internalCameraTMZMode = globals::CameraTMZMode;

	if (internalRapidFireToggle) {
		if (rapidFireWeaponComponent != nullptr) {
			for (int i = 0; i < globals::rapidFireCount; i++) {
				rapidFireWeaponComponent->Fire(1.0f);
			}
		}
	}
	Log::debug("test6");
	if (internalCameraTMZMode) {
		if (shareCameraPV != nullptr) {
			shareCameraPV->RpcPlayRemoteTakePictureFeedback(true);
		}
	}
	Log::debug("test7");
	SitOnHeadLoop();

	//Log::debug("OnUpdate_Ihook 111");
	Log::debug("test8");
	hook_manager::get()["Sleep"]->call<void>(instance, methodInfo);
	Log::debug("test9");
	return;
	//return OnUpdate_o(instance, methodInfo);
}

void __fastcall SafeCall_OnUpdate_o(void* params)
{
	auto pParams = static_cast<OnUpdateParamInfo*>(params);

	void*& instance = pParams->instance;
	void*& methodInfo = pParams->methodInfo;
	
	if (!globals::Ihooks::OnUpdate)
		return OnUpdate_o(instance, methodInfo);
		//return OnUpdate_o();

	if (const auto& updatePlayerlist = globals::updatePlayerlistOnUpdate;
		updatePlayerlist)
	{
		const auto currentTime = std::chrono::steady_clock::now();

		if (const auto elapsedTime250 = currentTime - lastExecutionTime250OU;
			elapsedTime250 > threshold250OU)
		{ // only every 250ms
			PlayerlistUpdate();
			ForceMasterClient();
			ShaderChamsLogic();
			CircuitsDisablerLogic();
			lastExecutionTime250OU = currentTime;
		}
	}
	
	if (globals::watchMenuTest) // hook priority check not needed here since this is an Ihook
		pWatchMenuHandler->Update();

	//if (globals::onUpdate::inExecution)
	OnUpdateQueueLogic();

	const auto& internalRapidFireToggle = globals::rapidFireToggle;
	const auto& internalCameraTMZMode = globals::CameraTMZMode;

	if (internalRapidFireToggle) {
		if (rapidFireWeaponComponent != nullptr) {
			for (int i = 0; i < globals::rapidFireCount; i++) {
				rapidFireWeaponComponent->Fire(1.0f);
			}
		}
	}

	if (internalCameraTMZMode) {
		if (shareCameraPV != nullptr) {
			shareCameraPV->RpcPlayRemoteTakePictureFeedback(true);
		}
	}

	SitOnHeadLoop();

	return OnUpdate_o(instance, methodInfo);
	//return OnUpdate_o();
}