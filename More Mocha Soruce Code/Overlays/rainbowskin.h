#pragma once

void RainbowSkin() {

	if (globals::colorSkin::toggle) {

		for (const auto& [photonPlayer, player] : cachedPlayerlist) {
			if (player.loadingStage >= LoadingStage::LOADED) {

				// could be better, idc smd
				if (player.isLocalPlayer) { if (!globals::colorSkin::self) continue; } 
				else { if (!globals::colorSkin::others) continue; }

				RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

				if (playerPlayer != nullptr) {

					if (playerPlayer->get_IsInitialized()) {

						void* PlayerAvatar = GetField<void*>(playerPlayer, 360);

						if (PlayerAvatar == nullptr) continue;

						PlayerAvatarDisplay* playerAvatarDisplay = GetField<PlayerAvatarDisplay*>(PlayerAvatar, 96);

						if (PlayerAvatar == nullptr) continue;

						float time = ImGui::GetTime() * globals::colorSkin::rainbowSpeed;
						float gradientFactor = fmodf(time, 2.0f);

						if (gradientFactor > 1.0f)
							gradientFactor = 2.0f - gradientFactor;

						Camera* camera = Camera::get_current();

						if (camera == nullptr) continue;

						Vector3 bodyPos = playerPlayer->get_CurrentBodyPosition();

						Vector2 w2sBody = camera->WorldToScreenPoint(bodyPos);

						ImGuiIO& io = ImGui::GetIO();

						float screenHeight = io.DisplaySize.y;
						float screenWidth = io.DisplaySize.x;

						float positionFactorBody = (w2sBody.x / screenWidth) * (w2sBody.y / screenHeight);
						float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

						float chosenFactor = (globals::colorSkin::self && player.isLocalPlayer) ? gradientFactor : combinedFactorBody;

						ImVec4 chosenColor = globals::colorSkin::rainbow ? GetRainbowColor(chosenFactor) : globals::colorSkin::color;
						float glow = globals::colorSkin::glow;

						if (globals::colorSkin::black)
							chosenColor = { -1.0f, -1.0f, -1.0f, 1.0f };
						
						playerAvatarDisplay->SetSkinColor(ImVec4{ (chosenColor.x + glow), (chosenColor.y + glow), (chosenColor.z + glow), chosenColor.w });

					}
				}
				
			}
		}

#ifdef oldshit
		Player localPlayer;

		for (const auto& [_, player] : cachedPlayerlist) {
			if (player.isLocalPlayer) {
				localPlayer = player;


				RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

				if (playerPlayer == nullptr) break;
				if (!playerPlayer->get_IsInitialized()) break;

				void* PlayerAvatar = GetField<void*>(playerPlayer, 328);

				if (PlayerAvatar == nullptr) break;

				void* PlayerAvatarDisplay = GetField<void*>(PlayerAvatar, 88);

				if (PlayerAvatar == nullptr) break;

				float time = ImGui::GetTime() * 1; // we should have different var for box but im lazy
				float gradientFactor = fmodf(time, 2.0f);

				if (gradientFactor > 1.0f)
					gradientFactor = 2.0f - gradientFactor;

				ImVec4 rainbowCola = GetRainbowColor(gradientFactor);

				SetSkinColor(PlayerAvatarDisplay, /*Color{(rainbowCola.x + 1), (rainbowCola.y + 1), (rainbowCola.z + 1), 0.5}*/Color{-1, -1, -1, 1.0});

				break;
			}
		}

#endif
	}

}