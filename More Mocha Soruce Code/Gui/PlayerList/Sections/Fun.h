#pragma once

void FunSection(PhotonPlayer*& photonPlayer)
{
    ImGui::SeparatorText("Energy Modules");

    ImGui::BeginDisabled();
    if (ImGui::Checkbox("Tower Game", &globals::energy::towerModuleToggle))
    {
        if (ThreadFix())
            newThread(&TowerGameDrop, photonPlayer);
    }
    ImGui::EndDisabled();

    ImGui::SameLine();
    
    if (ImGui::Button("Sit On Head")) {

        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitOnPlayerHeadTarget, photonPlayer);
    }
    ImGui::SetItemTooltip("Sit on his head! \nDon't forget to enable the loop in misc.");

    ImGui::SameLine();

    if (ImGui::Button("FVK")) {

        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::FakeVoteKickTarget, photonPlayer);
    }
    ImGui::SetItemTooltip("Display a fake vote kick message.");
    
    ImGui::SameLine();

    if (ImGui::Button("Lvl Up")) {

        EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::LevelUpTarget, photonPlayer);
    }
    ImGui::SetItemTooltip("Play level up effect.");
}