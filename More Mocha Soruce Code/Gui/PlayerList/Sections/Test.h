#pragma once

#ifndef PROD
void TestSection(PhotonPlayer*& photonPlayer)
{
    ImGui::SeparatorText("Test");

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

	ImGui::SameLine();

	if (ImGui::Button("Black Flash")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::BlackFlashTarget, photonPlayer);
	}

	ImGui::SameLine();

	if (ImGui::Button("Lagger")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LaggerTarget, photonPlayer);
	}

	ImGui::SameLine();

	if (ImGui::Button("epictest111")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::PlayerTest, photonPlayer);
	}

	ImGui::SameLine();

	if (ImGui::Button("gift test")) {

		EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GiftPlayerTest, photonPlayer);
	}
}
#endif