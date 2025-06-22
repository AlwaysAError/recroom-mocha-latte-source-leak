#pragma once
#include "../../Hooks/Pageguard/Small.h"
#include "../../Hooks/Pageguard/Universal.h"

void CGui::MovementTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Movement Modules");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Movement Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        //ImAdd::ToggleButtonClassic("Static Fly", &globals::Ihooks::AddFlyEnabled);
        if (ImAdd::ToggleButtonClassic("Static Fly", &globals::veh::fly))
        {
            globals::veh::fly ?
                veh::Hook((void*)methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled, &AddFlyEnabled_hook) :
                veh::Unhook((void*)methods::RecRoomCoreLocomotion::PlayerMovement::AddFlyEnabled);

            globals::veh::fly ?
                veh::Hook((void*)methods::RecRoomCoreLocomotion::PlayerMovement::RemoveFlyEnabled, &uNop_hook) :
                veh::Unhook((void*)methods::RecRoomCoreLocomotion::PlayerMovement::RemoveFlyEnabled);
        }
        ImGui::SetItemTooltip("Toggle static fly. (permissions)");

        ImGui::BeginDisabled();
        ImAdd::ToggleButtonClassic("Dynamic Fly", &globals::Ihooks::get_IsFlyingEnabled);
        ImGui::SetItemTooltip("Toggle dynamic fly. (client)");
        ImGui::EndDisabled();

        ImAdd::ToggleButtonClassic("Force Static Fly##22", &globals::staticFlyToggle);
        ImGui::SetItemTooltip("Forces flight permission every frame until recieved.");

        ImGui::Separator();
        ImAdd::ToggleButtonClassic("Packet Fly", &globals::packetfly::toggle);
        ImGui::SetItemTooltip("Fly by movement packets. \n Change Steam VR Bindings to use in VR. \nControls: \nWASD - move \nSpace - up \nLCTRL - down \nLShift - 2x Speed");

        if (globals::packetfly::toggle) {
            ImGui::Indent(10);
            ImAdd::BeginHighlightGroup();

            ImAdd::ToggleButton("Horizontal", &globals::packetfly::horizontal);
            ImAdd::ToggleButton("Vertical", &globals::packetfly::vertical);
            ImAdd::ToggleButton("Lock Y-Axis", &globals::packetfly::lockVertical);
            if (globals::packetfly::vertical) {
                ImGui::InputFloat("Vertical Speed ", &globals::packetfly::verticalSpeed);
                ImGui::InputDouble("Vertical Factor", &globals::packetfly::verticalFactor);
            }
            if (globals::packetfly::horizontal) {
                ImGui::InputFloat("Horizontal Speed ", &globals::packetfly::horizontalSpeed);
            }

            ImAdd::EndHighlightGroup();
            ImGui::Indent(-10);
        }

        ImGui::Separator();
        ImGui::InputFloat("Gravity x", &globals::gravity.x);
        ImGui::InputFloat("Gravity y", &globals::gravity.y);
        ImGui::InputFloat("Gravity z", &globals::gravity.z);

        if (ImGui::Button("Set gravity")) {
            Physics::set_gravity(globals::gravity);
        }

#ifndef PROD
        ImGui::SameLine();

        if (ImGui::Button("Get Gravity")) {
            std::cout << "[>] Current gravity is: " << Physics::get_gravity() << "\n";
        }
#endif

        ImGui::SameLine();
        if (ImGui::Button("Restore Gravity")) {
            Physics::set_gravity({ 0.0f, -9.81f, 0.0f });
        }
    }
    ImGui::EndChild();

}
