#pragma once

bool IsSelectableFiltered(const char* selectable, const char* filter) {
    return strstr(selectable, filter) != nullptr;
}

void toLowercaseInPlace(std::string& str)
{
    for (char& c : str)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
}

void toLowercaseInPlace(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = std::tolower(static_cast<unsigned char>(str[i]));
    }
}

void CGui::AssetsSpawnTab(ImGuiStyle& style) {

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
    ImGui::PushFont(m_Fonts.BigFont);
    {
        ImGui::TextDisabled("Assets Spawn");
    }
    ImGui::PopFont();
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
    ImGui::BeginChild("Assets Spawn", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    {
        if (pHookManager->hookPriority == HookManager::HookType::PAGEGUARD) {
            if (ImAdd::ToggleButton("Asset Spawn Override: ", &globals::veh::assetspawn)) {
                if (!pHookManager->UpdateHooks())
                    Log::error("rehook failed!");
            }
        }
        else {
            ImAdd::ToggleButton("Asset Spawn Override: ", &globals::Ihooks::InstantiateAssets);
        }

        if (ImAdd::Button("Spawn Asset", ImVec2(-0.1f, 0)))
        {
            EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnAssetOnTarget, localPlayer.photonPlayer);
        }
        ImGui::SetItemTooltip("Spawn a prefab.");

        static float internalScale[3] = { 1.0, 1.0, 1.0 };

        static float internalRandomScaleX[2] = { 0, 0 };
        static float internalRandomScaleY[2] = { 0, 0 };
        static float internalRandomScaleZ[2] = { 0, 0 };

        // using ToggleButtonClassic so it can sameline

        ImAdd::ToggleButtonClassic("Custom Item Type ##1", &globals::instantiateAssets::prefabTypeToggle);
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("Custom Vectors ##1", &globals::instantiateAssets::vectorsToggle);

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Random Scale ##1", &globals::instantiateAssets::randomScaleToggle);
#ifndef PROD
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("Debug Output ##1", &globals::instantiateAssets::debugToggle);
#endif

        ImGui::Separator();
#ifndef CHEAP
        ImAdd::ToggleButtonClassic("Infinity Exploit ##1", &globals::instantiateAssets::infinityToggle);
        ImGui::SameLine(); HelpMarker("Spawns item at infinity.");
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("Black Flash Exploit ##1", &globals::instantiateAssets::blackFlashToggle);
        ImGui::SameLine(); HelpMarker("Crash every player in the lobby after dart spawns. \nYou have 5~ seconds to leave before it takes effect.");
#endif
        ImGui::Separator();
#ifdef CHEAP
        ImAdd::ToggleButtonClassic("Green Card ##1", &globals::instantiateAssets::returnTypeFixToggle);
        ImGui::SameLine(); HelpMarker("Bypass crashing on bosses and stuff.");
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("No Menu Close ##1", &globals::instantiateAssets::returnTypeNULLToggle);
        ImGui::SameLine(); HelpMarker("Bypass menu closing when overidden.");
#else
        ImAdd::ToggleButtonClassic("RT Fix Toggle ##1", &globals::instantiateAssets::returnTypeFixToggle);
        ImGui::SameLine(); HelpMarker("Return the original GameObject* to avoid detections.");
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("NULL RT Toggle ##1", &globals::instantiateAssets::returnTypeNULLToggle);
        ImGui::SameLine(); HelpMarker("Return a nullptr causing exceptions in some menus which prevent them from closing.");
#endif

        ImGui::Separator();

        ImAdd::ToggleButtonClassic("Despawn Toggle ##1", &globals::instantiateAssets::despawnToggle);
        ImGui::SameLine(); HelpMarker("Toggle whether or not the item will despawn when you leave the room.");
        ImGui::SameLine(175);
        ImAdd::ToggleButtonClassic("Advanced Config ##1", &globals::instantiateAssets::advancedConfigToggle);

        ImGui::Separator();

        /* old button layout, whitelists not included in new one
        ImGui::Checkbox("Custom Vectors", &globals::instantiateAssets::vectorsToggle);
        ImGui::SameLine(175);
        ImGui::Checkbox("Polaroid Whitelist", &globals::instantiateAssets::polaroidWhitelistToggle);
        ImGui::Checkbox("Custom Item Type", &globals::instantiateAssets::prefabTypeToggle);
        ImGui::SameLine(175);
        ImGui::Checkbox("Player Spawn Whitelist", &globals::instantiateAssets::playerSpawnWhitelistToggle);
        ImGui::Checkbox("Random Scale", &globals::instantiateAssets::randomScaleToggle);
        ImGui::SameLine(175);
        ImGui::Checkbox("Debug Output", &globals::instantiateAssets::debugToggle);
        ImGui::Checkbox("Infinity Exploit", &globals::instantiateAssets::infinityToggle);
        ImGui::SameLine(175);
        ImGui::Checkbox("RT Fix Toggle", &globals::instantiateAssets::returnTypeFixToggle);
        ImGui::Checkbox("NULL RT Toggle", &globals::instantiateAssets::returnTypeNULLToggle);
        ImGui::SameLine(175);
        ImGui::Checkbox("Advanced Config", &globals::instantiateAssets::advancedConfigToggle);
        ImGui::Checkbox("Despawn Toggle", &globals::instantiateAssets::despawnToggle);
        */

        ImGui::SliderInt("Additional Spawns ##1", &globals::instantiateAssets::Count, 0, 200); // 50mb is photon buffer size

        if (!globals::instantiateAssets::randomScaleToggle) {
            ImGui::InputFloat3("Scale ##1", internalScale);
        }
        else {
            ImGui::Separator();

            ImGui::InputFloat2("X | Min/Max ##1", internalRandomScaleX);
            ImGui::InputFloat2("Y | Min/Max ##1", internalRandomScaleY);
            ImGui::InputFloat2("Z | Min/Max ##1", internalRandomScaleZ);

            std::copy(std::begin(internalRandomScaleX), std::end(internalRandomScaleX), std::begin(globals::instantiateAssets::randomScaleX));
            std::copy(std::begin(internalRandomScaleY), std::end(internalRandomScaleY), std::begin(globals::instantiateAssets::randomScaleY));
            std::copy(std::begin(internalRandomScaleZ), std::end(internalRandomScaleZ), std::begin(globals::instantiateAssets::randomScaleZ));
        }

        globals::instantiateAssets::scale.x = internalScale[0];
        globals::instantiateAssets::scale.y = internalScale[1];
        globals::instantiateAssets::scale.z = internalScale[2];

        if (globals::instantiateAssets::advancedConfigToggle) {

            ImGui::Separator();

            static char prefabBufferShareCamera[256] = "";
            static char prefabBufferFeedbackTool[256] = "";
            static char prefabBufferStreamerCam[256] = "";

            ImGui::InputTextWithHint(("##1"), ("ShareCamera"), prefabBufferShareCamera, IM_ARRAYSIZE(prefabBufferShareCamera));
            ImGui::InputTextWithHint(("##2"), ("FeedbackTool"), prefabBufferFeedbackTool, IM_ARRAYSIZE(prefabBufferFeedbackTool));
            ImGui::InputTextWithHint(("##3"), ("StreamerCam"), prefabBufferStreamerCam, IM_ARRAYSIZE(prefabBufferStreamerCam));
            ImGui::SameLine(); HelpMarker("Turn on RT Fix and turn off NULL RT on StreamerCam or you will be detected.");

            globals::instantiateAssets::prefabShareCamera = prefabBufferShareCamera;
            globals::instantiateAssets::prefabFeedbackTool = prefabBufferFeedbackTool;
            globals::instantiateAssets::prefabStreamerCam = prefabBufferStreamerCam;
        }

        if (globals::instantiateAssets::vectorsToggle) {
            ImGui::Separator();

            static float internalPosition[3] = { 0, 0, 0 };
            static float internalRotation[4] = { 0, 0, 0, 0 };

            ImGui::InputFloat3("Position ##1", internalPosition);
            ImGui::InputFloat4("Rotation ##1", internalRotation);

            globals::instantiateAssets::position.x = internalPosition[0];
            globals::instantiateAssets::position.y = internalPosition[1];
            globals::instantiateAssets::position.z = internalPosition[2];

            globals::instantiateAssets::rotation.w = internalRotation[0];
            globals::instantiateAssets::rotation.x = internalRotation[1];
            globals::instantiateAssets::rotation.y = internalRotation[2];
            globals::instantiateAssets::rotation.z = internalRotation[3];
        }

        if (globals::instantiateAssets::infinityToggle) {
            ImGui::Separator();
            ImAdd::ToggleButton("Scale Toggle ##1", &globals::instantiateAssets::infinityScaleToggle);
            if (globals::instantiateAssets::infinityScaleToggle)
                ImAdd::ToggleButton("Positive/Negative ##1", &globals::instantiateAssets::infinityScaleType);
        }

        if (globals::instantiateAssets::prefabTypeToggle) {
            ImGui::Separator();

            // Static variables: filterText for string handling, inputBuffer for ImGui input
            static std::string filterText = "";
            static char inputBuffer[256] = "";

            // Input text field
            ImGui::InputTextWithHint("##90", "Enter Prefab Here", inputBuffer, IM_ARRAYSIZE(inputBuffer));
            // Convert input to lowercase and sync with filterText
            toLowercaseInPlace(inputBuffer);
            filterText = inputBuffer;

            ImGui::SameLine();
            if (ImGui::Button("Paste ##1")) {
                const char* clipboardText = ImGui::GetClipboardText();
                if (clipboardText) {
                    // Convert clipboard text to lowercase
                    std::string temp = clipboardText;
                    toLowercaseInPlace(temp);
                    filterText = temp;
                    // Sync with inputBuffer, ensuring null-termination
                    strncpy_s(inputBuffer, filterText.c_str(), sizeof(inputBuffer) - 1);
                    inputBuffer[sizeof(inputBuffer) - 1] = '\0';
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Clear ##1")) {
                // Clear both filterText and inputBuffer
                filterText.clear();
                inputBuffer[0] = '\0';
            }

            // Filtering loop: filterText is already lowercase
            for (int i = 0; i < IM_ARRAYSIZE(prefabList); ++i) {
                // Create a lowercase version of the prefab item
                std::string lowerPrefab = prefabList[i];
                toLowercaseInPlace(lowerPrefab);

                // Check if the item passes the filter
                if (IsSelectableFiltered(lowerPrefab.c_str(), filterText.c_str())) {
                    // Display selectable with original case; copy to clipboard if selected
                    if (ImGui::Selectable(prefabList[i])) {
                        ImGui::SetClipboardText(prefabList[i]);
                    }
                }
            }

            // Assign the lowercase filter text to prefab
            globals::instantiateAssets::prefab = filterText;
        }

        /*
        if (globals::instantiateAssets::prefabTypeToggle) {
            ImGui::Separator();

            static char filterBuffer[256] = "";
            ImGui::InputTextWithHint("##90", "Enter Prefab Here", filterBuffer, IM_ARRAYSIZE(filterBuffer));

            ImGui::SameLine();
            if (ImGui::Button("Paste ##1")) {
                const char* clipboardText = ImGui::GetClipboardText();
                if (clipboardText) {
                    if (strlen(filterBuffer) > 0) {
                        memset(filterBuffer, 0, sizeof(filterBuffer));
                    }
                    strncpy_s(filterBuffer, clipboardText, IM_ARRAYSIZE(filterBuffer) - 1);
                }
            }

            ImGui::SameLine();
            if (ImGui::Button("Clear ##1")) {
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
            globals::instantiateAssets::prefab = filterBuffer;
        }
        */
    }
    ImGui::EndChild();

}