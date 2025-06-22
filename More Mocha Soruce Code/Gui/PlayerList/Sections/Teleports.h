#pragma once

void TeleportsSection(PhotonPlayer*& photonPlayer)
{
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
}