#include <cstdint>

#include "globals.h"

void globals::opRaiseEventEdit::EditInfo::SetActorIDs(ActorIDsPreset preset, uint32_t targetID) { //! this is here because playerlist shit isn't in scope in globals
	targetActorIDs.clear();
	switch (preset) {
	case (ActorIDsPreset::Others): {

		for (const auto& [_, player] : cachedPlayerlist) {
			if (!player.isLocalPlayer)
				targetActorIDs.push_back(player.photonActorID);
		}

		break;
	}
	case (ActorIDsPreset::Target): {
		targetActorIDs.push_back(targetID);
		break;
	}
	default:
		break;
	}
}

template<typename Func, typename... Args>
void EnqueueCallback(const std::chrono::milliseconds timeout,
					 const globals::onUpdate::ExecutionCondition condition,
					 Func&& func, 
					 Args&&... args)
{
	using namespace std::chrono;
	std::unique_lock lock(globals::onUpdate::queueMutex, std::defer_lock);

	if (!lock.try_lock_for(500ms)) {
		Log::error("queueMutex timed out in EnqueueCallback!");
		return;
	}

	auto args_tuple = std::make_tuple(std::forward<Args>(args)...);
    
	globals::onUpdate::callbackQueue.emplace_back(globals::onUpdate::QueuedCallback{
		[func = std::forward<Func>(func),
		 captured_args = std::move(args_tuple)]() mutable {
			return std::apply(func, std::move(captured_args));
		},
		steady_clock::now(),  // Capture enqueue time
		timeout,
		condition
	});
}