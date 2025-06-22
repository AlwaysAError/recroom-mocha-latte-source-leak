#pragma once

void CGui::ItemsSpawnTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Items Spawn");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Items Spawn", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD) {
            if (ImAdd::ToggleButton("Item Spawn Override: ", &globals::veh::itemspawn)) {
                if (!pHookManager->UpdateHooks())
                    Log::error("rehook failed!");
            }
        }
        else
            ImAdd::ToggleButton("Item Spawn Override: ", &globals::Ihooks::Instantiate);

        if (ImAdd::Button("Spawn Item", ImVec2(-0.1f, 0)))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnItemOnTarget, localPlayer.photonPlayer);
        }

        static float internalScale[3] = { 1.0, 1.0, 1.0 };
        static float internalRandomScaleX[2] = { 0, 0 };
        static float internalRandomScaleY[2] = { 0, 0 };
        static float internalRandomScaleZ[2] = { 0, 0 };

        ImAdd::ToggleButtonClassic("Custom Item Type", &globals::instantiate::prefabTypeToggle);
        ImGui::SameLine(192);
        ImAdd::ToggleButtonClassic("Custom Vectors", &globals::instantiate::vectorsToggle);

        ImAdd::ToggleButtonClassic("Random Scale", &globals::instantiate::randomScaleToggle);
        ImGui::SameLine(192);
        ImAdd::ToggleButtonClassic("Debug Output", &globals::instantiate::debugToggle);

        ImAdd::ToggleButtonClassic("Infinity Exploit", &globals::instantiate::infinityToggle);
        ImGui::SameLine(); HelpMarker("Spawns item at infinity.");
        ImGui::SameLine(192);
        ImAdd::ToggleButtonClassic("Black Flash Exploit", &globals::instantiate::blackFlashToggle);
        ImGui::SameLine(); HelpMarker("Crash every player in the lobby after dart spawns. \nYou have 5~ seconds to leave before it takes effect.");

        ImAdd::ToggleButtonClassic("RT Fix Toggle", &globals::instantiate::returnTypeFixToggle);
        ImGui::SameLine(); HelpMarker("Return the original GameObject* to avoid detections.");
        ImGui::SameLine(192);
        ImAdd::ToggleButtonClassic("NULL RT Toggle", &globals::instantiate::returnTypeNULLToggle);
        ImGui::SameLine(); HelpMarker("Return a nullptr causing exceptions in some menus which prevent them from closing.");

        ImAdd::ToggleButtonClassic("Player Spawn Whitelist", &globals::instantiate::playerSpawnWhitelistToggle);
        ImGui::SameLine(); HelpMarker("Whitelist the player spawn prefabs only.");
        ImGui::SameLine(192);
        ImAdd::ToggleButtonClassic("Polaroid Whitelist", &globals::instantiate::polaroidWhitelistToggle);
        ImGui::SameLine(); HelpMarker("Whitelist polaroid prefabs only.");

        ImGui::SliderInt("Additional Spawns", &globals::instantiate::Count, 0, 200); // 50mb is photon buffer size

        if (!globals::instantiate::randomScaleToggle) {
            ImGui::InputFloat3("Scale", internalScale);
        }
        else {
            ImGui::Separator();

            ImGui::InputFloat2("X | Min/Max", internalRandomScaleX);
            ImGui::InputFloat2("Y | Min/Max", internalRandomScaleY);
            ImGui::InputFloat2("Z | Min/Max", internalRandomScaleZ);

            std::copy(std::begin(internalRandomScaleX), std::end(internalRandomScaleX), std::begin(globals::instantiate::randomScaleX));
            std::copy(std::begin(internalRandomScaleY), std::end(internalRandomScaleY), std::begin(globals::instantiate::randomScaleY));
            std::copy(std::begin(internalRandomScaleZ), std::end(internalRandomScaleZ), std::begin(globals::instantiate::randomScaleZ));
        }

        globals::instantiate::scale.x = internalScale[0];
        globals::instantiate::scale.y = internalScale[1];
        globals::instantiate::scale.z = internalScale[2];

        if (globals::instantiate::vectorsToggle) {
            ImGui::Separator();

            static float internalPosition[3] = { 0, 0, 0 };
            static float internalRotation[4] = { 0, 0, 0, 0 };

            ImGui::InputFloat3("Position", internalPosition);
            ImGui::InputFloat4("Rotation", internalRotation);

            globals::instantiate::position.x = internalPosition[0];
            globals::instantiate::position.y = internalPosition[1];
            globals::instantiate::position.z = internalPosition[2];

            globals::instantiate::rotation.w = internalRotation[0];
            globals::instantiate::rotation.x = internalRotation[1];
            globals::instantiate::rotation.y = internalRotation[2];
            globals::instantiate::rotation.z = internalRotation[3];
        }

        if (globals::instantiate::infinityToggle) {
            ImGui::Separator();
            ImAdd::ToggleButtonClassic("Scale Toggle", &globals::instantiate::infinityScaleToggle);
            if (globals::instantiate::infinityScaleToggle)
                ImAdd::ToggleButtonClassic("Positive/Negative", &globals::instantiate::infinityScaleType);
        }

        /*
        if (globals::instantiate::prefabTypeToggle) {
            ImGui::Separator();

            static char filterBuffer[256] = "";
            ImGui::InputTextWithHint("##89", "Enter Prefab Here", filterBuffer, IM_ARRAYSIZE(filterBuffer));

            ImGui::SameLine();
            if (ImGui::Button("Paste")) {
                const char* clipboardText = ImGui::GetClipboardText();
                if (clipboardText) {
                    if (strlen(filterBuffer) > 0) {
                        memset(filterBuffer, 0, sizeof(filterBuffer));
                    }
                    strncpy_s(filterBuffer, clipboardText, IM_ARRAYSIZE(filterBuffer) - 1);
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                memset(filterBuffer, 0, sizeof(filterBuffer));
            }

            toLowercaseInPlace(filterBuffer);

            for (int i = 0; i < IM_ARRAYSIZE(prefabList); ++i) {
                static int selected = -1;

                char lowerFoodItem[128];
                strcpy_s(lowerFoodItem, prefabList[i]);
                toLowercaseInPlace(lowerFoodItem);

                if (IsSelectableFiltered(lowerFoodItem, filterBuffer)) {
                    if (ImGui::Selectable(prefabList[i], selected == i)) {
                        ImGui::SetClipboardText(prefabList[i]);
                        selected = -1;
                    }
                }
            }
            globals::instantiate::prefab = filterBuffer;
        }
        */

        if (globals::instantiate::prefabTypeToggle) {
            ImGui::Separator();

            // Static variables for filter text and ImGui input buffer
            static std::string filterText = "";
            static char inputBuffer[256] = "";

            // Input text field with hint; update filterText when input changes
            if (ImGui::InputTextWithHint("##89", "Enter Prefab Here", inputBuffer, IM_ARRAYSIZE(inputBuffer))) {
                filterText = inputBuffer;
            }

            ImGui::SameLine();
            if (ImGui::Button("Paste")) {
                const char* clipboardText = ImGui::GetClipboardText();
                if (clipboardText) {
                    // Clear filterText if not empty, then set to clipboard content
                    if (!filterText.empty()) {
                        filterText.clear();
                    }
                    filterText = clipboardText;
                    // Sync inputBuffer with filterText, ensuring no overflow
                    strncpy_s(inputBuffer, filterText.c_str(), sizeof(inputBuffer) - 1);
                    inputBuffer[sizeof(inputBuffer) - 1] = '\0';
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Clear")) {
                filterText.clear();
                inputBuffer[0] = '\0';
            }

            // Create a lowercase version of filterText for case-insensitive filtering
            std::string lowerFilterText = filterText;
            toLowercaseInPlace(lowerFilterText);

            for (int i = 0; i < IM_ARRAYSIZE(prefabList); ++i) {
                // Create a lowercase version of the prefab item for filtering
                std::string lowerPrefab = prefabList[i];
                toLowercaseInPlace(lowerPrefab);

                if (IsSelectableFiltered(lowerPrefab.c_str(), lowerFilterText.c_str())) {
                    if (ImGui::Selectable(prefabList[i])) {
                        ImGui::SetClipboardText(prefabList[i]);
                    }
                }
            }

            // Assign filterText to the global prefab variable
            globals::instantiate::prefab = filterText;
        }
        
    } 
    ImGui::EndChild();

}