#pragma once
#include "../Modules/Callbacks/SpawnAsset.h"

Il2CppObject* clothingSaved;
Il2CppObject* propertiesSaved;

void PlayerlistLegacy() {

	if (/*globals::legacyPlayerlist*/true) {

		ImGui::Begin("Legacy Player List", nullptr);

		for (auto& photonPlayer : photonPlayerlist) {

			auto it = cachedPlayerlist.find(photonPlayer);
			if (it != cachedPlayerlist.end()) {

				PlayerInfo player = cachedPlayerlist[photonPlayer];

				std::string playerCurrentName = player.DisplayName; // Use c_str() for ImGui 

				RecRoomPlayer* recPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

				std::string PlayerNameString;

				recPlayer != nullptr ?
					PlayerNameString = " [" + std::to_string(player.photonActorID) + "] " + playerCurrentName + " (" + std::to_string(recPlayer->get_Ping()) + "ms) "
					:
					PlayerNameString = " [" + std::to_string(player.photonActorID) + "] " + playerCurrentName + " ";

				if (player.loadingStage < LoadingStage::LOADED) {
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f)); // orange
				}
				else if (player.isLocalPlayer) {
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // green
				}
				else {
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); // white
				}

				bool renderExtra = true;
				if (ImGui::CollapsingHeader(PlayerNameString.c_str())) {

					renderExtra = false;

					if (player.isVanished) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.749f, 0.608f, 0.839f, 1.0f)); // blue-ish

						ImGui::Text("[V]");
						ImGui::SetItemTooltip("Vanished Player Detected.");

						ImGui::PopStyleColor();
					}

					if ((player.loadingStage >= LoadingStage::PHOTON) && PhotonNetwork::get_isMasterClient(photonPlayer)) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f)); // purple

						ImGui::Text("[M]");
						ImGui::SetItemTooltip("Master Client.");

						ImGui::PopStyleColor();
					}

					if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // red

						ImGui::Text("[VMOD]");
						ImGui::SetItemTooltip("Blacklisted Player.");

						ImGui::PopStyleColor();
					}

					if (recPlayer != nullptr) {
						ImGui::Indent(15);
						if (ImGui::CollapsingHeader("Player Information")) {

							std::string hardwareTypeString = "Hardware Type: " + RecPlayerHardwareTypeToString(recPlayer->get_HardwareType());
							ImGui::Text(hardwareTypeString.c_str());

							std::string deviceClassString = "Device Class: " + RecPlayerRecNetDeviceClassToString(recPlayer->get_RecNetDeviceClass());
							ImGui::Text(deviceClassString.c_str());

							ImGui::Text("RR+ Visible: ");
							ImGui::SameLine();
							if (recPlayer->get_HasVisibleRecRoomPlus()) {
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // green
								ImGui::Text("True");
								ImGui::PopStyleColor();
							}
							else {
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // red
								ImGui::Text("False");
								ImGui::PopStyleColor();
							}

							ImGui::Text("Friend: ");
							ImGui::SameLine();
							if (recPlayer->get_IsFriend()) {
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // green
								ImGui::Text("True");
								ImGui::PopStyleColor();
							}
							else {
								ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // red
								ImGui::Text("False");
								ImGui::PopStyleColor();
							}

							if (player.hasChamsChild) {
								ImGui::Text("Has Chams Child.");
								{
									//Renderer* renderer = (Renderer*)player.playerGameObject->GetComponent("Renderer");
								}
							}
							
							ImGui::Text(std::string("PlayerID: " + std::string(player.playerID)).c_str());
						}
						ImGui::SetItemTooltip("Show extra player information.");
						ImGui::Unindent(15);
					}

					ImGui::SeparatorText("Exploits");

					if (ImGui::Button("Set Royalty"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SetMasterClientTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Set victim as Master Client.");

					ImGui::SameLine();

					if (ImGui::Button("Kick"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::RespawnAtInfinityTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Attempt to kick the victim by exploit.");
					if (!player.isLocalPlayer) {
#ifndef PROD
						ImGui::SameLine();

						if (ImGui::Button("Bye-Bye"))
						{
							EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ByeByeExploitTarget, photonPlayer);
						}
						ImGui::SetItemTooltip("Delete victim by exploit.");
#endif

						//ImGui::SeparatorText("Disconnects");

						ImGui::SameLine();

						if (ImGui::Button("Freeze"))
						{
							EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FreezeTarget, photonPlayer);
						}
						ImGui::SetItemTooltip("Freeze victim by exploit.");

						ImGui::SameLine();

						if (ImGui::Button("Ev207"))
						{
							EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DestroyPhotonPlayerTarget, photonPlayer);
						}
						ImGui::SetItemTooltip("Send a DestroyPlayer event to the victim.");

						ImGui::SameLine();

						if (ImGui::Button("RAM Crash"))
						{
							EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BulletCrashTarget, photonPlayer);
						}
						ImGui::SetItemTooltip("Crashes victim by exploit. \nRIP system RAM.");

#ifndef PROD
						ImGui::SameLine();

						if (ImGui::Button("Death")) {

							EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DeathTarget, photonPlayer);
						}
						ImGui::SetItemTooltip("Goodbye my nigger back to the lobby! :P");
#endif
					}

					ImGui::SeparatorText("Teleports");

					if (ImGui::Button("Grab"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToMeTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Teleport victim to you.");

					ImGui::SameLine();

					if (ImGui::Button("Teleport"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Teleport to victim.");

#ifdef pldebug
					ImGui::SameLine();

					if (ImGui::Button("DebugTP"))
					{
						newThread(&newPlayerList::TeleportToPlayerDebugPL, photonPlayer);
					}
					ImGui::SetItemTooltip("Teleport to victim but with debug.");
#endif

					ImGui::SameLine();

					if (ImGui::Button("Teleport All"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportAllToTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Teleport everyone to victim.");

					ImGui::SameLine();

					if (ImGui::Button("Void"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToLimitTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Teleport victim to really far out (the limit for teleports).");

					ImGui::SameLine();

					if (ImGui::Button("Respawn"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::RespawnPlayerTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Respawn the victim to force them to drop any held objects.");

					ImGui::SameLine();

					if (ImGui::Button("Despawn"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::DespawnPlayerTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Despawn the victim's player.");

					ImGui::SameLine();

					if (ImGui::Button("Spawn"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SpawnPlayerTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Spawn the victim's player.");

					ImGui::SeparatorText("Misc");

					if (ImGui::Button("Spawn Item"))
					{
						EnqueueCallback(std::chrono::milliseconds(500), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SpawnAssetOnTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Spawn an item on the victim. \nCustomizable with Assets Spawn, turn off RT Fix & NULL RT.");

					ImGui::SameLine();

					if (ImGui::Button("Jedi"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::JediTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Put the cached item in the victim's hand. \nCustomizable with Assets Spawn.");

					ImGui::SameLine();

					if (ImGui::Button("Msg CV1"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ShowNotificationTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Send a message onto the victim's screen.");

					ImGui::SameLine();

					if (ImGui::Button("Msg CV2")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ShowBannerNotificationTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Send a CV2 message onto the victim's screen.");

					ImGui::SameLine();

					if (ImGui::Button("Promotion"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::UpdateRolesTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Boss, give this man a promotion!");

					ImGui::SeparatorText("Fun Modules");

					if (ImGui::Button("SitTarget"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitTarget, photonPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("Add Godmode")) {

						std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

						if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {
							cachedPlayerlist[photonPlayer].hasGodmodeWhitelist = true;

							lock.unlock();
						}
						else {
							Log::error("playerlistMutex timed out in Add Godemode Button!");
						}
					}

					ImGui::SameLine();

					if (ImGui::Button("Revoke Godmode")) {

						std::unique_lock<std::timed_mutex> lock(playerlistMutex, std::defer_lock);

						if (lock.try_lock_for(std::chrono::milliseconds(globals::playerlistMutexTimeout))) {

							cachedPlayerlist[photonPlayer].hasGodmodeWhitelist = false;

							lock.unlock();
						}
						else {
							Log::error("playerlistMutex timed out in Revoke Godemode Button!");
						}
					}

					#ifndef PROD
					ImGui::SameLine();

					if (ImGui::Button("Clothing"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceHoldClothingTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("1. Open clothing giftbox, make sure clothing is spawned. \n2. Press this button.");
					#endif
					
					ImGui::SameLine();

					if (ImGui::Button("Exterminate"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::ExterminateTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Make him go boom!");

					if (ImGui::Button("HEAT")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::PlayAudioSampleTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Play audio for player. \nConfig in Exploits.");

					ImGui::SameLine();

					if (ImGui::Button("FVK")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FakeVoteKickTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Display a fake vote kick message.");

					ImGui::SameLine();

					if (ImGui::Button("Fling")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FlingTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Fling target. \nConfig in misc.");

					ImGui::SameLine();

					if (ImGui::Button("Lvl Up")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LevelUpTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Play level up effect.");
					
					if (ImGui::Button("Start Party")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::JoinPartyTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Start a party with them. \nInvites do not work. \nYou must not be in a party to use this.");

					ImGui::SameLine();

					if (ImGui::Button("Join Party")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::JoinPartyTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Join their party. \nParty invites do not work.");

					ImGui::SameLine();

					if (ImGui::Button("Leave Party")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LeavePartyTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Force leave party exploit.");

					if (ImGui::Button("Sit On Head")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitOnPlayerHeadTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Sit on his head! \nDon't forget to enable the loop in misc.");

					
					
					ImGui::SeparatorText("Energy Modules");

					if (ImGui::Checkbox("Tower Game", &globals::energy::towerModuleToggle))
					{
						if (ThreadFix())
							newThread(&TowerGameDrop, photonPlayer);
					}

#ifndef PROD

					ImGui::SameLine();

					if (ImGui::Button("Ban"))
					{
						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceMakerPenTarget, photonPlayer);
					}
					ImGui::SetItemTooltip("Ban victim's account by exploit. \nOnly working in #RRO worlds. \nDoes not work for VMOD/Staff accounts. \nBan will take some hours to apply.");

					ImGui::SameLine();

					if (ImGui::Button("cprops"))
					{
						ThreadFix();

						Log::debug(ReadIl2CppString(photonPlayer->get_CustomProperties()->ToString()));

					}

					ImGui::SameLine();

					if (ImGui::Button("Slave")) {

						ThreadFix();

						PhotonPlayer* targetPP = nullptr;

						for (const auto& [PhotonPlayer, player] : cachedPlayerlist) {
							if (player.photonActorID == globals::slaveID) {
								targetPP = photonPlayer;
								break;
							}
						}

						if (targetPP != nullptr) {
							PlayerInfo& targetPlayer = cachedPlayerlist[photonPlayer];
							targetPlayer.photonView->TransferOwnership(targetPP);
						}
						else {
							Log::debug("faiel cuh");
						}
					}

					ImGui::SeparatorText("New Shit");

					if (ImGui::Button("Black Flash")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BlackFlashTarget, photonPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("Lagger")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LaggerTarget, photonPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("GAS")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::GoToRoomTarget, photonPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("epictest111")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::PlayerTest, photonPlayer);
					}

					ImGui::SameLine();

					if (ImGui::Button("gift test")) {

						EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GiftPlayerTest, photonPlayer);
					}
#endif
				}

				if (renderExtra) {

					if (player.isVanished) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.749f, 0.608f, 0.839f, 1.0f)); // blue-ish

						ImGui::Text("[V]");
						ImGui::SetItemTooltip("Vanished Player Detected.");

						ImGui::PopStyleColor();
					}

					if (PhotonNetwork::get_isMasterClient(photonPlayer)) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f)); // purple

						ImGui::Text("[M]");
						ImGui::SetItemTooltip("Master Client.");

						ImGui::PopStyleColor();

					}

					if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
						ImGui::SameLine();
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // red

						ImGui::Text("[VMOD]");
						ImGui::SetItemTooltip("Blacklisted Player.");

						ImGui::PopStyleColor();
					}
				}

				ImGui::PopID();
				if (player.isLocalPlayer || (player.loadingStage >= LoadingStage::LOADED) || !renderExtra) {
					ImGui::PopStyleColor();
				}

			}
		}
		ImGui::End();
	}
}