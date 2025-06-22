#pragma once
#include <variant>

bool OnUpdateQueueLogic() {
	using namespace std::chrono;
	std::unique_lock lock(globals::onUpdate::queueMutex, std::defer_lock);

	if (!lock.try_lock_for(500ms)) {
		Log::error("queueMutex timeout in OnUpdateQueueLogic!");
		return false;
	}

	auto& callbackQueue = globals::onUpdate::callbackQueue;
	const auto now = steady_clock::now();

	auto it = callbackQueue.begin();
	while (it != callbackQueue.end()) {
		// Check timeout first
		if (const auto elapsed = now - it->enqueue_time;
			elapsed > it->timeout) {
			it = callbackQueue.erase(it);
			continue;
		}

		// Check execution condition
		bool should_execute = false;
		switch(it->condition) {
		case globals::onUpdate::ExecutionCondition::ExecInstant:
			should_execute = true;
			break;
		case globals::onUpdate::ExecutionCondition::ExecLoaded:
			if (localPlayerExists && localPlayer.loadingStage >= LoadingStage::LOADED)
			{
				if (auto* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);
					playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished())
				{
					should_execute = true;
				}
			}
			break;
		}

		if (!should_execute) {
			++it;
			continue;
		}

		// Execute and check completion
		if (it->function()) {
			it = callbackQueue.erase(it);
		} else {
			++it;
		}
	}

	return true;
}

typedef void(*OnUpdate_t)(void*, void*);
void __fastcall OnUpdate_hook(void* InputManager, void* methodInfo) {
	
	const auto func = (OnUpdate_t)(methods::RecRoomSystems::InputManager::OnUpdate);

	Log::debug("OnUpdate_hook");
	
	if (OnUpdateQueueLogic())
		globals::veh::onUpdate = false;

	pHookManager->UpdateHooks();

	return func(InputManager, methodInfo);
}

typedef void(*PreformMainLoop_t)();
PreformMainLoop_t PreformMainLoop_o = nullptr;
void PreformMainLoop_hook()
{
	const auto func = (PreformMainLoop_t)reinterpret_cast<void*>(PreformMainLoop_o);
	
	//Log::debug("PreformMainLoop_hook");

	return veh::CallOriginal<void>(func);
}