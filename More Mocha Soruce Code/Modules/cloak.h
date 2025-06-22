#pragma once

std::string cloakNotificationString = "";

void Cloak() {

	if (globals::cloakToggle) {
		if (localPlayer.loadingStage >= LoadingStage::LOADED) {

			RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

			if (localPlayerPlayer != nullptr) {

				if (localPlayerPlayer->get_IsInitialized()) {

					for (auto& [photonPlayer, player] : cachedPlayerlist) {
						if (!player.hasTriggeredCloak && ((player.loadingStage >= LoadingStage::LOADED) && (!player.hasBeenCrashed))) {

							RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

							if (playerPlayer != nullptr) {

								if (playerPlayer->get_IsInitialized()) {

									if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {

										ThreadFix();
										/*
										PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
										PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
										PlayerList::FreezePlayerPL(localPlayer.photonPlayer);
										*/

										std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock); // FreezeTarget has it's own lock

										if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

											localPlayer.isVanished = true;

											player.hasTriggeredCloak = true;

											cloakNotificationString = "Cloak Triggered by: " + std::string(player.DisplayName) + ".";

											pGui->notify.PushNotification<ImVec4(0, 0, 1, 1), 3.0f>(pGui->m_pTextures->tWingFilled, cloakNotificationString);

											STARTUPINFO si;
											PROCESS_INFORMATION pi;

											ZeroMemory(&si, sizeof(si));
											si.cb = sizeof(si);
											ZeroMemory(&pi, sizeof(pi));

											if (CreateProcess(NULL, LPSTR("cmd /c audio.bat"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
											{
												CloseHandle(pi.hProcess);
												CloseHandle(pi.hThread);
											}
										}
										else {
											Log::error("playerlistMutex timed out in Cloak!");
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}