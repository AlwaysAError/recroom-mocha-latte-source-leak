#pragma once

std::string skillGapNotificationString = "";

void SkillGap() {

	if (globals::skillGapToggle) {

		if (localPlayer.loadingStage >= LoadingStage::LOADED) {

			RecRoomPlayer* localPlayerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

			if (localPlayerPlayer != nullptr) {

				if (localPlayerPlayer->get_IsInitialized()) {

					for (auto& [photonPlayer, player] : cachedPlayerlist) {
						if ((player.loadingStage >= LoadingStage::LOADED) && (!player.hasBeenCrashed)) {

							RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

							if (playerPlayer != nullptr) {

								if (playerPlayer->get_IsInitialized()) {

									if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {

										ThreadFix();

										Sleep(1000);

										if (!PhotonNetwork::get_isMasterClient(localPlayer.photonPlayer)) {
											if (!PhotonNetwork::set_MasterClient(localPlayer.photonPlayer)) {
												Log::error("Failed to set master client for: " + std::string(localPlayer.DisplayName));
												return;
											}
											Sleep(250);
										}

										//newThread(&PlayerList::BulletCrashPL, photonPlayer);

										player.hasBeenCrashed = true;

										skillGapNotificationString = "Reddit Moderator Crashed: " + std::string(player.DisplayName) + "!";

										pGui->notify.PushNotification<ImVec4(1, 0, 0, 1), 3.0f>(pGui->m_pTextures->tExplosion, skillGapNotificationString);

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
								}
							}
						}
					}
				}
			}
		}
	}

}