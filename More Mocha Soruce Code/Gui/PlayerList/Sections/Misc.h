#pragma once

void MiscSection(PhotonPlayer*& photonPlayer)
{
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

	ImGui::BeginDisabled();
	
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

	ImGui::EndDisabled();
	
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

	if (ImGui::Button("Fling")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FlingTarget, photonPlayer);
	}
	ImGui::SetItemTooltip("Fling target. \nConfig in misc.");

	ImGui::SameLine();
	
	if (ImGui::Button("Start Party")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::JoinMyPartyTarget, photonPlayer);
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
	
}