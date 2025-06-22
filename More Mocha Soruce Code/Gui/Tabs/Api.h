#pragma once

void CGui::ApiTab(ImGuiStyle& style) {

#ifndef PROD

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Api Modules");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Api Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD) {
            if (ImAdd::ToggleButtonClassic("Toggle Chai", &globals::Ihooks::chai/*&globals::veh::chai*/)) {
                //if (!pHookManager->UpdateHooks())
                    //Log::error("rehook failed!");
            }
            ImGui::SetItemTooltip("Toggle legacy chai (Safe Mode).");

            if (globals::Ihooks::chai/*globals::veh::chai*/) {

                ImGui::Indent(10);
                ImAdd::BeginHighlightGroup();

                if (ImGui::Button("Refresh Config")) {
                    Configs::Load::Chai();
                }
                ImGui::SetItemTooltip("Refresh Chai Config.");

                ImAdd::ToggleButtonClassic("Toggle Swaps", &globals::chai::swapsToggle);
                ImGui::SetItemTooltip("Toggle link swapping.");

                ImAdd::ToggleButtonClassic("Debug Swapped", &globals::chai::debugToggle);
                ImGui::SetItemTooltip("Debug all swapped links.");

                ImAdd::ToggleButtonClassic("Debug All", &globals::chai::debugAllToggle);
                ImGui::SetItemTooltip("Debug all links.");

                ImAdd::EndHighlightGroup();
                ImGui::Indent(-10);
            }
        }
        else {
            ImAdd::ToggleButtonClassic("Toggle Chai", &globals::Ihooks::chai);
            ImGui::SetItemTooltip("Toggle Chai (Experimental Mode). \nTURNING THIS OFF MAY CRASH/BAN YOU!");

            if (globals::Ihooks::chai) {

                ImGui::Indent(10);
                ImAdd::BeginHighlightGroup();

                if (ImGui::Button("Refresh Config")) {
                    Configs::Load::Chai();
                }
                ImGui::SetItemTooltip("Refresh Chai Config.");

                ImAdd::ToggleButtonClassic("Toggle Swaps", &globals::chai::swapsToggle);
                ImGui::SetItemTooltip("Toggle link swapping.");

                ImAdd::ToggleButtonClassic("Debug Swapped", &globals::chai::debugToggle);
                ImGui::SetItemTooltip("Debug all swapped links.");

                ImAdd::ToggleButtonClassic("Debug All", &globals::chai::debugAllToggle);
                ImGui::SetItemTooltip("Debug all links.");

                ImAdd::EndHighlightGroup();
                ImGui::Indent(-10);
            }

        }


        ImGui::Separator();
        ImAdd::ToggleButtonClassic("Sigma Sigma (on the wall)", &globals::Ihooks::GenerateRequestSignature);

        if (globals::Ihooks::GenerateRequestSignature) {

            ImGui::InputTextWithHint("##8911", "put sigma here", &globals::xrnsig::urlBuffer);

        }

    }
    ImGui::EndChild();
#endif
}