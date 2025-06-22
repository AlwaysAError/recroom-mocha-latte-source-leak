#pragma once

void TowerGameDrop(PhotonPlayer* pPlayer);

namespace PL {
    enum TabType : int {
        None,
        Exploits,
        Teleports,
        Misc,
        Fun,
        Info,
        Dev,
    };

    const char* GetTabName(int ID) {
        switch (ID)
        {
        case Exploits:
            return "Exploits";
            break;
        case Teleports:
            return "Teleports";
            break;
        case Misc:
            return "Misc";
            break;
        case Fun:
            return "Fun";
            break;
        case Info:
            return "Info";
            break;
        case Dev:
            return "Dev";
            break;
        default:
            return "*UNKNOW*";
            break;
        }
    }

    const char* GetTabDescription(int ID) {
        switch (ID)
        {
        case Exploits:
            return "Break game";
            break;
        case Teleports:
            return "Teleport players";
            break;
        case Misc:
            return "Random shit.";
            break;
        case Fun:
            return "No Diddy.";
            break;
        case Info:
            return "Player Information.";
            break;
        case Dev:
            return "Skliggas ON TOP.";
            break;
        default:
            return "*UNKNOW* Description Here ...";
            break;
        }
    }

}

int tabType = PL::Exploits;

void CGui::PlayerListGUI(ImGuiStyle& style) {

    renderPlayerlist.clear();

    for (auto& photonPlayer : photonPlayerlist) {

        auto it = cachedPlayerlist.find(photonPlayer);
        if (it != cachedPlayerlist.end()) {

            PlayerInfo& player = cachedPlayerlist[photonPlayer];
            ImVec4 chosenColor = ImVec4(241.0f / 255.0f, 243.0f / 255.0f, 245.0f / 255.0f, 1.0f); // white
            ImVec4 chosenIconColor = ImVec4(241.0f / 255.0f, 243.0f / 255.0f, 245.0f / 255.0f, 1.0f); // white
            ID3D11ShaderResourceView* chosenIcon = m_pTextures->tUsersFilled;

            if (player.loadingStage < LoadingStage::LOADED) {
                chosenColor = ImVec4(255.0f / 255.0f, 195.0f / 255.0f, 71.0f / 255.0f, 1.0f); // yellow
                chosenIconColor = ImVec4(255.0f / 255.0f, 195.0f / 255.0f, 71.0f / 255.0f, 1.0f); // yellow
                chosenIcon = m_pTextures->tLoading;
            }
            if ((player.loadingStage >= LoadingStage::LOADED) && player.isLocalPlayer) {
                chosenColor = ImVec4(71.0f / 255.0f, 255.0f / 255.0f, 167.0f / 255.0f, 1.0f); // green
                chosenIconColor = ImVec4(71.0f / 255.0f, 255.0f / 255.0f, 167.0f / 255.0f, 1.0f); // green
                chosenIcon = m_pTextures->tCrown;
            }
            else if (player.loadingStage < LoadingStage::LOADED && player.isLocalPlayer) {
                chosenColor = ImVec4(71.0f / 255.0f, 255.0f / 255.0f, 167.0f / 255.0f, 1.0f); // green
                chosenIconColor = ImVec4(255.0f / 255.0f, 195.0f / 255.0f, 71.0f / 255.0f, 1.0f); // yellow
                chosenIcon = m_pTextures->tLoading;
            }
            if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
                chosenColor = ImVec4(181.0f / 255.0f, 25.0f / 255.0f, 25.0f / 255.0f, 1.0f); // red
                chosenIconColor = ImVec4(181.0f / 255.0f, 25.0f / 255.0f, 25.0f / 255.0f, 1.0f); // red
                chosenIcon = m_pTextures->tWarnFilled;
            }
            if (player.loadingStage >= LoadingStage::LOADED) {

                RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                if (playerPlayer != nullptr) {
                    if (playerPlayer->get_IsInitialized()) {
                        if (playerPlayer->get_IsFriend()) {
                            chosenColor = ImVec4(0.0f, 0.7f, 1.0f, 1.0f); // blueish
                            if (chosenIcon == m_pTextures->tUsersFilled)
                                chosenIconColor = ImVec4(0.0f, 0.7f, 1.0f, 1.0f); // blueish
                        }
                    }
                }
            }
            if ( PhotonNetwork::get_isMasterClient(player.photonPlayer)) {
                chosenIconColor = ImVec4(193.0f / 255.0f, 77.0f / 255.0f, 255.0f / 255.0f, 1.0f); // magenta
                chosenIcon = m_pTextures->tCrown;
            }

            renderPlayerlist.push_back({ player, chosenColor, chosenIconColor, chosenIcon });
        }
    }

    if (globals::PopOutPlayerlist)
        ImGui::Begin("Player List", nullptr, ImGuiWindowFlags_NoTitleBar);

    ImGui::BeginChild("BgMain", ImVec2(0, 0), 0, ImGuiWindowFlags_NoBackground);
    {
        float fControlPanelHeight = style.WindowPadding.y * 2 + ImGui::GetFrameHeight() * 3 + ImGui::GetFontSize() + style.ItemSpacing.y * 45;

        static int iSelectedUser = -1;

        ImGui::BeginChild("List", ImVec2(0, ImGui::GetWindowHeight() - fControlPanelHeight), 0, ImGuiWindowFlags_NoBackground);
        {
            if (!renderPlayerlist.empty())
            {

                for (int i = 0; i < renderPlayerlist.size(); i++)
                {
                    RecRoomPlayer* recPlayer = nullptr;

                    if (renderPlayerlist[i].player.loadingStage >= LoadingStage::LOADED)
                        recPlayer = RecRoomPlayer::GetFromActorNumber(renderPlayerlist[i].player.photonActorID);

                    std::string PlayerNameString;

                    recPlayer != nullptr ?
                        PlayerNameString = " [" + std::to_string(renderPlayerlist[i].player.photonActorID) + "] " + renderPlayerlist[i].player.DisplayName + " (" + std::to_string(recPlayer->get_Ping()) + "ms) "
                        :
                        PlayerNameString = " [" + std::to_string(renderPlayerlist[i].player.photonActorID) + "] " + renderPlayerlist[i].player.DisplayName;

                    ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_Header]);
                    ImGui::PushStyleColor(ImGuiCol_TextDisabled, renderPlayerlist[i].vec4Color);
                    ImGui::PushStyleColor(ImGuiCol_SliderGrab, renderPlayerlist[i].vec4Color);
                    ImAdd::RadioFrameIconColor(PlayerNameString.c_str(), renderPlayerlist[i].tIcon, &iSelectedUser, i, renderPlayerlist[i].iconColor, ImVec2(-0.1f, 0));
                    ImGui::PopStyleColor(3);
                }
            }
        }
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGui::EndChild();
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
        ImGui::BeginChild("ControlPanel", ImVec2(0, 0), ImGuiChildFlags_Border);
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        {
            if (iSelectedUser == -1 || renderPlayerlist.empty() || iSelectedUser > renderPlayerlist.size())
            {
                ImGui::SetCursorPos(ImGui::GetWindowSize() / 2 - ImGui::CalcTextSize("Select a player") / 2);
                ImGui::TextDisabled("Select a player");
            }
            else
            {
                const float SideBarWidth = 90;

                ImGui::BeginChild("SideBar", ImVec2(SideBarWidth, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
                {
                    // Push a new style color for the child background (green in this case)
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 1.0f, 0.0f, 1.0f)); // Green color

                    // Remove the border color
                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());

                    ImVec2 radioSize = ImVec2(ImGui::GetWindowWidth() - style.WindowPadding.x * 2, 0);

                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, style.ChildRounding);
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, style.Colors[ImGuiCol_PopupBg]);
                    {
                        ImAdd::SeparatorText("CATEGORIES");
                        {
                            ImAdd::RadioFrame("Exploits", &tabType, PL::Exploits, radioSize);
                            ImAdd::RadioFrame("Teleports", &tabType, PL::Teleports, radioSize);
                            ImAdd::RadioFrame("Misc", &tabType, PL::Misc, radioSize);
                            ImAdd::RadioFrame("Fun", &tabType, PL::Fun, radioSize);
                            ImAdd::RadioFrame("Info", &tabType, PL::Info, radioSize);
#ifndef PROD
                            ImAdd::RadioFrame("Dev", &tabType, PL::Dev, radioSize);
#endif
                        }
                    }
                    ImGui::PopStyleColor(); // Pop FrameBg color
                    ImGui::PopStyleVar();   // Pop FrameRounding
                    ImGui::PopStyleColor(); // Pop Border color
                    ImGui::PopStyleColor(); // Pop ChildBg color
                }
                ImGui::EndChild();

                ImGui::EndChild();
                ImGui::SameLine(SideBarWidth);
                ImGui::BeginChild("Content", ImVec2(0, 0), ImGuiChildFlags_Border, ImGuiWindowFlags_NoBackground);
                {
                    ImGui::BeginGroup();
                    {
                        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, style.ItemInnerSpacing);
                        {
                            ImGui::Spacing();
                            ImGui::PushFont(m_Fonts.BigFont);
                            {
                                ImGui::Text(PL::GetTabName(tabType));
                            }
                            ImGui::PopFont();
                            ImGui::SameLine();
                            ImGui::TextDisabled(PL::GetTabDescription(tabType));
                        }
                        ImGui::PopStyleVar();
                    }
                    ImGui::EndGroup();

                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4());
                    ImGui::BeginChild("Playerlist Modules", ImVec2(0, (ImGui::GetFontSize() * 2 + style.WindowPadding.y * 4 + style.ItemInnerSpacing.y) + (style.WindowPadding.y * 2 + ImGui::GetFontSize() * 6 + style.ItemInnerSpacing.y * 3) + (ImGui::GetFontSize() + style.WindowPadding.y * 2) * 10), ImGuiChildFlags_Border);
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                    {

                        auto& selectedPlayer = renderPlayerlist[iSelectedUser];
                        PlayerInfo& player = selectedPlayer.player;
                        PhotonPlayer*& photonPlayer = player.photonPlayer;

                        RecRoomPlayer* recPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

                        std::string PlayerNameString;

                        recPlayer != nullptr ?
                            PlayerNameString = " [" + std::to_string(player.photonActorID) + "] " + player.DisplayName + " (" + std::to_string(recPlayer->get_Ping()) + "ms)"
                            :
                            PlayerNameString = " [" + std::to_string(player.photonActorID) + "] " + player.DisplayName;

                        if ((player.loadingStage >= LoadingStage::PHOTON) && PhotonNetwork::get_isMasterClient(player.photonPlayer)) {
                            PlayerNameString += " [M]";
                        }

                        if (IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
                            PlayerNameString += " [VMOD]";
                        }

                        ImAdd::DoubleText(style.Colors[ImGuiCol_Text], selectedPlayer.vec4Color, "Selected User:", PlayerNameString.c_str());

                        ImGui::Separator();

                        switch (tabType) {

                        case (PL::Exploits): {

                            if (ImGui::Button("Set Royalty"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecInstant, Callbacks::SetMasterClientTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Set victim as Master Client.");

                            ImGui::SameLine();

                            if (ImGui::Button("Kick"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::RespawnAtInfinityTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Attempt to kick the victim by exploit.");
                            if (!player.isLocalPlayer) {
#ifndef PROD
                                ImGui::SameLine();

                                if (ImGui::Button("Bye-Bye"))
                                {
                                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ByeByeExploitTarget, photonPlayer);
                                }
                                ImGui::SetItemTooltip("Delete victim by exploit.");
#endif

                                //ImGui::SeparatorText("Disconnects");

                                ImGui::SameLine();

                                if (ImGui::Button("Freeze"))
                                {
                                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::FreezeTarget, photonPlayer);
                                }
                                ImGui::SetItemTooltip("Freeze victim by exploit.");

                                ImGui::SameLine();

                                if (ImGui::Button("Ev207"))
                                {
                                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DestroyPhotonPlayerTarget, photonPlayer);
                                }
                                ImGui::SetItemTooltip("Send a DestroyPlayer event to the victim.");

                                ImGui::SameLine();

                                if (ImGui::Button("RAM Crash"))
                                {
                                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::BulletCrashTarget, photonPlayer);
                                }
                                ImGui::SetItemTooltip("Crashes victim by exploit. \nRIP system RAM.");

#ifndef PROD
                                ImGui::SameLine();

                                if (ImGui::Button("Death")) {

                                    EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DeathTarget, photonPlayer);
                                }
                                ImGui::SetItemTooltip("Goodbye my nigger back to the lobby! :P");
#endif
                            }

                            break;
                        }
                        case (PL::Teleports): {

                            if (ImGui::Button("Grab"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToMeTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Teleport victim to you.");

                            if (ImGui::Button("Teleport"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Teleport to victim.");

#ifdef pldebug

                            if (ImGui::Button("DebugTP"))
                            {
                                newThread(&newPlayerList::TeleportToPlayerDebugPL, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Teleport to victim but with debug.");
#endif

                            if (ImGui::Button("Teleport All"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportAllToTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Teleport everyone to victim.");

                            if (ImGui::Button("Void"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::TeleportToLimitTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Teleport victim to really far out (the limit for teleports).");


                            if (ImGui::Button("Respawn"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::RespawnPlayerTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Respawn the victim to force them to drop any held objects.");

                            ImGui::SameLine();

                            if (ImGui::Button("Despawn"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::DespawnPlayerTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Despawn the victim's player.");

                            ImGui::SameLine();

                            if (ImGui::Button("Spawn"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnPlayerTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Spawn the victim's player.");

                            break;
                        }
                        case (PL::Misc): {

                            if (ImGui::Button("Spawn Item"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SpawnAssetOnTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Spawn an item on the victim. \nCustomizable with Assets Spawn, turn off RT Fix & NULL RT.");

                            if (ImGui::Button("Jedi"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::JediTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Put the cached item in the victim's hand. \nCustomizable with Assets Spawn.");

                            ImGui::InputTextWithHint("##89122", "put message here", &globals::messagePLBuffer);

                            if (ImGui::Button("Message"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ShowNotificationTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Send a message onto the victim's screen.");

                            if (ImGui::Button("Promotion"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::UpdateRolesTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Boss, give this man a promotion!");

                            if (ImGui::Button("Clothing"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceHoldClothingTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("1. Open clothing giftbox, make sure clothing is spawned. \n2. Press this button.");

                            if (ImGui::Button("Exterminate"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ExterminateTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Make him go boom!");

                            break;
                        }
                        case (PL::Fun): {

                            if (ImGui::Button("Cuck-Chair")) {

                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::SitTarget, photonPlayer);

                            }

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

                            break;
                        }
                        case (PL::Info): {

                            RecRoomPlayer* recPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);
                            PhotonPlayer*& photonPlayer = player.photonPlayer;

                            if (recPlayer != nullptr) {

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
                            }

                            break;
                        }
#ifndef PROD
                        case (PL::Dev): {

                            if (ImGui::Checkbox("Tower Game", &globals::energy::towerModuleToggle))
                            {
                                if (ThreadFix())
                                    newThread(&TowerGameDrop, photonPlayer);
                            }

                            if (ImGui::Button("Ban"))
                            {
                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::ForceMakerPenTarget, photonPlayer);
                            }
                            ImGui::SetItemTooltip("Ban victim's account by exploit. \nOnly working in #RRO worlds. \nDoes not work for VMOD/Staff accounts. \nBan will take some hours to apply.");

                            if (ImGui::Button("cprops"))
                            {
                                ThreadFix();

                                Log::debug(ReadIl2CppString(photonPlayer->get_CustomProperties()->ToString()));

                            }

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

                            if (ImGui::Button("Black Flash")) {

                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::BlackFlashTarget, photonPlayer);
                            }

                            if (ImGui::Button("Lag To Fuck")) {

                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::LaggerTarget, photonPlayer);
                            }

                            if (ImGui::Button("GAS")) {

                                EnqueueCallback(std::chrono::milliseconds(300), globals::onUpdate::ExecutionCondition::ExecLoaded, Callbacks::GoToRoomTarget, photonPlayer);
                            }

                            break;
                        }
#endif
                        default:

                            ImGui::SetCursorPos(ImGui::GetWindowSize() / 2 - ImGui::CalcTextSize("Select a tab") / 2);
                            ImGui::TextDisabled("Select a tab");

                            break;
                        }
                    }
                    ImGui::EndChild();
                }
            }
            ImGui::EndChild();
        }
    }
    ImGui::EndChild();

    if (globals::PopOutPlayerlist)
        ImGui::End();
}

void CGui::PlayerListTab(ImGuiStyle& style) {

    if (ImGui::CollapsingHeader("Player List Options")) {
        ImGui::Indent(10);
        ImAdd::BeginHighlightGroup();
#ifndef PROD
        ImAdd::ToggleButtonClassic("Update Playerlist OnUpdate", &globals::updatePlayerlistOnUpdate);
        ImAdd::ToggleButtonClassic("Unlock Playerlist Mutex On 3 Fails", &globals::unlockPlayerlistMutexOnFails);
#endif
        ImAdd::ToggleButtonClassic("Legacy PlayerList", &globals::legacyPlayerlist);
        ImGui::SetItemTooltip("Use Legacy Player List (not maintained).");
        ImAdd::ToggleButtonClassic("Pop Out", &globals::PopOutPlayerlist);
        ImGui::SetItemTooltip("Pop out the Player List onto a seperate window.");

        ImAdd::EndHighlightGroup();
        ImGui::Indent(-10);
    }

    if (!globals::PopOutPlayerlist)
        PlayerListGUI(style);
}