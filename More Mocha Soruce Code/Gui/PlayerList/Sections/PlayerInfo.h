#pragma once

void PlayerInfoSection(PlayerInfo& player, RecRoomPlayer*& playerPlayer)
{
    ImGui::Indent(15);
    if (ImGui::CollapsingHeader("Player Information")) {

        std::string hardwareTypeString = "Hardware Type: " + RecPlayerHardwareTypeToString(playerPlayer->get_HardwareType());
        ImGui::Text(hardwareTypeString.c_str());

        std::string deviceClassString = "Device Class: " + RecPlayerRecNetDeviceClassToString(playerPlayer->get_RecNetDeviceClass());
        ImGui::Text(deviceClassString.c_str());

        ImGui::Text("RR+ Visible: ");
        ImGui::SameLine();
        if (playerPlayer->get_HasVisibleRecRoomPlus()) {
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
        if (playerPlayer->get_IsFriend()) {
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