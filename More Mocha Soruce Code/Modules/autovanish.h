#pragma once

void AutoVanish() {

	if (globals::autoVanishToggle) {

		if ((localPlayer.loadingStage >= LoadingStage::RECROOM) && (!localPlayer.isVanished)) {
			/*
			PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
			PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
			PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
			*/

			std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock); // FreezeTarget has it's own lock

			if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

				auto& cachedplayer = cachedPlayerlist[localPlayer.photonPlayer];
				cachedplayer.isVanished = true;
				localPlayer.isVanished = true;

				lock.unlock();

				pGui->notify.PushNotification<ImVec4(0, 1, 0.5, 1), 3.0f>(pGui->m_pTextures->tStar, "Auto-Vanish Triggered.");
			}
			else {
				Log::error("playerlistMutex timed out in AutoVanish!");
			}
		}
	}
}