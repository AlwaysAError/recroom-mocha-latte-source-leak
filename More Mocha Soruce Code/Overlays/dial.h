#pragma once

enum ButtonIndex : int {
	FREEZE,
	DESPAWN,
	SPAWN,
	TELEPORT,
	GRAB,
	DROPTOOLS,
	BULLETCRASH,
	FLING,
};

bool clickedMiddleMouseButton = false;
bool onPlayer = false;
Vector3 bodyPosDial{ 0, 0, 0 };
int selectedPlayerActorID = -1;
const char* playerNameOnDial = "";
std::vector<bool> wasHovered(8, false);
std::vector<const char*> buttonNames(8, "Button");
int buttonNum = FREEZE;

bool IsMouseInCircle(const ImVec2& circleCenter, float radius) {

	ImGuiIO& io = ImGui::GetIO();
	float screenHeight = io.DisplaySize.y;
	float screenWidth = io.DisplaySize.x;

	ImVec2 screenCenter = ImVec2(screenWidth / 2.0f, screenHeight / 2.0f);

	float dx = screenCenter.x - circleCenter.x;
	float dy = screenCenter.y - circleCenter.y;
	float distanceSquared = dx * dx + dy * dy;

	return distanceSquared <= (radius * radius);
}

bool IsMouseInRect(const ImVec2& min, const ImVec2& max) {

	ImGuiIO& io = ImGui::GetIO();
	float screenHeight = io.DisplaySize.y;
	float screenWidth = io.DisplaySize.x;

	ImVec2 screenCenter = ImVec2(screenWidth / 2.0f, screenHeight / 2.0f);

	return (screenCenter.x >= min.x && screenCenter.x <= max.x) && (screenCenter.y >= min.y && screenCenter.y <= max.y);
}

void dial() {
	if (!onPlayer && !clickedMiddleMouseButton && (GetAsyncKeyState(VK_MBUTTON) & 0x8000))
	{
		clickedMiddleMouseButton = true;

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("Dial Player Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);


		auto draw = ImGui::GetWindowDrawList();

		float screenHeight = io.DisplaySize.y;
		float screenWidth = io.DisplaySize.x;

		for (const auto& [photonPlayer, player] : cachedPlayerlist) {
			ThreadFix();
			if ((player.loadingStage >= LoadingStage::LOADED) && !player.isLocalPlayer) {
				RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

				if (playerPlayer != nullptr) {

					if (playerPlayer->get_IsInitialized()) {
						Vector3 headPos = playerPlayer->get_CurrentHeadPosition();
						Vector3 bodyPos = playerPlayer->get_CurrentBodyPosition();

						Camera* camera = Camera::get_current();

						if (camera == nullptr) {
							Log::error("camera is nullptr");
						}

						Vector2 w2sHead = camera->WorldToScreenPoint(headPos);
						Vector2 w2sBody = camera->WorldToScreenPoint(bodyPos);

						Vector3 cameraPosition = camera->get_gameObject()->get_transform()->get_position();
						Quaternion cameraRotation = camera->get_gameObject()->get_transform()->get_localRotation();

						Vector3 directionToPlayer = headPos - cameraPosition;
						float angleToPlayer = Vector3::angle(camera->get_gameObject()->get_transform()->get_forward(), directionToPlayer);
						float playerFOV = camera->get_fieldOfView();

						if (angleToPlayer < playerFOV) {
							float minX = w2sBody.x;
							float minY = screenHeight - w2sBody.y;
							float maxX = w2sBody.x;
							float maxY = screenHeight - w2sBody.y;

							if (w2sHead.x < minX) minX = w2sHead.x;
							if (w2sHead.x > maxX) maxX = w2sHead.x;
							if (screenHeight - w2sHead.y < minY) minY = screenHeight - w2sHead.y;
							if (screenHeight - w2sHead.y > maxY) maxY = screenHeight - w2sHead.y;

							float padding = 35.0f;
							ImVec2 min = ImVec2(minX - padding, minY - padding);
							ImVec2 max = ImVec2(maxX + padding, maxY + padding);

							// was used for debug
							//draw->AddRect(min, max,  ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 1.0f, 1.0f)), 1.0f); // Red box

							if (IsMouseInRect(min, max))
							{
								bodyPosDial = bodyPos;
								selectedPlayerActorID = player.photonActorID;
								playerNameOnDial = ReadIl2CppString(playerPlayer->getPlayerName());
								onPlayer = true;

								break;
							}
						}
					}
				}
			}
		}
		ImGui::End();

	}

	if ((GetAsyncKeyState(VK_MBUTTON) & 0x8000) && onPlayer) {

		// shit fix ik
		ThreadFix();

		if (selectedPlayerActorID < 0)
			return;

		RecRoomPlayer* targetPlayer = RecRoomPlayer::GetFromActorNumber(selectedPlayerActorID);

		if (targetPlayer != nullptr) {

			if (!targetPlayer->get_IsInitialized()) {
				return;
			}
		}

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("Dial Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs);

		auto draw = ImGui::GetWindowDrawList();

		float screenHeight = io.DisplaySize.y;
		float screenWidth = io.DisplaySize.x;

		ImVec2 screenCenter = ImVec2(screenWidth * 0.5f, screenHeight * 0.5f);

		Camera* camera = Camera::get_current();

		if (camera == nullptr) {
			Log::error("camera is nullptr");
		}

		int radius = 200;
		//Vector3 vecZero = { 0, 0, 0 };
		auto w2sPos = camera->WorldToScreenPoint(bodyPosDial);

		draw->AddCircleFilled(ImVec2(w2sPos.x, screenHeight - w2sPos.y), radius, IM_COL32(0, 0, 0, 128));

		draw->AddCircle(ImVec2(w2sPos.x, screenHeight - w2sPos.y), radius, IM_COL32(255, 255, 255, 255), 32);

		ImVec2 textPos = ImVec2(w2sPos.x, screenHeight - w2sPos.y);
		ImVec2 textSize = ImGui::CalcTextSize(playerNameOnDial);
		ImVec2 textOffset = ImVec2(-textSize.x * 0.5f, -textSize.y * 0.5f);
		draw->AddText(textPos + textOffset, IM_COL32(173, 216, 230, 255), playerNameOnDial);

		float buttonRadius = 60.0f;
		float angleStep = 2 * MY_PI / 8;

		for (int i = 0; i < 8; ++i) {
			float angle = i * angleStep;
			ImVec2 buttonPos = ImVec2(w2sPos.x, screenHeight - w2sPos.y) + ImVec2(cos(angle) * (radius - buttonRadius), sin(angle) * (radius - buttonRadius));

			ImVec2 min = buttonPos - ImVec2(buttonRadius, buttonRadius);
			ImVec2 max = buttonPos + ImVec2(buttonRadius, buttonRadius);

			if (IsMouseInCircle(buttonPos, buttonRadius)) {

				buttonRadius = buttonRadius + 20.0f;

				wasHovered.at(i) = true;
				buttonNum = i;
			}
			else
			{
				buttonRadius = 60.0f;
				wasHovered.at(i) = false;
			}

			draw->AddCircle(buttonPos, buttonRadius, IM_COL32(0, 255, 0, 255), 32);

			ImVec2 textPos2 = buttonPos;
			ImVec2 textSize2 = ImGui::CalcTextSize(buttonNames.at(i));
			ImVec2 textOffset2 = ImVec2(-textSize2.x * 0.5f, -textSize2.y * 0.5f);
			draw->AddText(textPos2 + textOffset2, IM_COL32(255, 255, 255, 255), buttonNames.at(i));
		}
		ImGui::End();
	}
	else
	{
		onPlayer = false;
		for (bool wasHover : wasHovered)
		{
			if (wasHover)
			{

				ThreadFix();

				if (selectedPlayerActorID < 0)
					return;

				RecRoomPlayer* targetPlayer = RecRoomPlayer::GetFromActorNumber(selectedPlayerActorID);

				if (targetPlayer != nullptr) {

					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
				}

				wasHovered.at(buttonNum) = false;

				switch (buttonNum) {
				case FREEZE: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GoToRoomTarget, photonPlayer);
					break;
				}
				case DESPAWN: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DespawnPlayerTarget, photonPlayer);
					break;
				}
				case SPAWN: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnPlayerTarget, photonPlayer);
					break;
				}
				case TELEPORT: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToTarget, photonPlayer);
					break;
				}
				case GRAB: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToMeTarget, photonPlayer);
					break;
				}
				case DROPTOOLS: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::RespawnPlayerTarget, photonPlayer);
					break;
				}
				case BULLETCRASH: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::BulletCrashTarget, photonPlayer);
					break;
				}
				case FLING: {
					if (!targetPlayer->get_IsInitialized()) {
						return;
					}
					PhotonPlayer* photonPlayer = targetPlayer->get_PhotonPlayer();
					EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::FlingTarget, photonPlayer);
					break;
				}
				}
			}
		}
	}
	if (((GetAsyncKeyState(VK_MBUTTON) & 0x8000) == 0) && clickedMiddleMouseButton)
	{
		clickedMiddleMouseButton = false;
	}
}